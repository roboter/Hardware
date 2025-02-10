//document.querySelector(".top_header").insertAdjacentHTML('beforebegin', '<div class=" container-fluide text-center fst-italic bg-primary-subtle py-2">Уважаемые пользователи, 23 февраля мы не работаем. </div>');
function decrement(e) {
    var value = parseInt(document.getElementById(e).value, 10);
    if (value > 1 && !isNaN(value)) {
        value--;
        document.getElementById(e).value = value;
        serverCart(e, value);
    }
}
function increment(e) {
    var value = document.getElementById(e).value;
    if (value < 9999 && !isNaN(value)) {
        value++;
        document.getElementById(e).value = value;
        serverCart(e, value);
    }
}
function morph(int, array) {
    return (array = array || ['товар', 'товара', 'товаров']) && array[(int % 100 > 4 && int % 100 < 20) ? 2 : [2, 0, 1, 1, 1, 2][(int % 10 < 5) ? int % 10 : 5]];
}

function cartPopup(tovarov, arrayOfGoods) {
    var htmlText = '<div class="cart-popup__uptext"><p class="m-0">В корзине: <b>' + tovarov["tovarov"] + '</b> ' + morph(tovarov["tovarov"]) + '</p><u role="button" onclick="eraseCart()">Очистить корзину</u></div><hr class="cart-popup__hrgreen"/><div class="cart-popup__tovars overflow-auto p-2">';
    arrayOfGoods.forEach((goods) => { // рисуем корзину
        htmlText += '<div class="cart-popup__card"><div><a href="https://compacttool.ru/' + goods["chpu"] + '"><img class="cart-popup__cardimg" src="https://cdn.compacttool.ru/images/min/' + goods["id"] + '_1.jpg"></a></div><div><div class="cart-popup__cardtext"><p class="cart-popup__cardp m-0">' + goods["name"] + '</p><i role="button" class="icon-cancel-circle" title="Удалить из корзины" onclick="delFromCart(' + goods["id"] + ')"></i></div><div class="cart-popup__bottom"><p class="cart-popup__cardprice"><small><i>арт</i> <b>' + goods["art"] + '</b></small></p><p class="cart-popup__cardprice"><i>' + goods["tov_qty"] + ' шт</i> х <b>' + goods["price"] + 'р</b></p></div></div></div><hr class="cart-popup__hrgray"/>';
    });
    htmlText += '</div><div class="cart-popup__bottom"><a href="https://compacttool.ru/korzina/" class="btn btn-outline-success">В КОРЗИНУ</a><p class="cart-popup__bottomp"> <small>Итого:</small> <b>' + tovarov["total"] + ' р.</b></p></div>';
    return htmlText;
}

async function addToCart(id) {
    var val = document.getElementById(id).value;
    if (val < 1 || isNaN(val)) { document.getElementById(id).value = 1; val = 1; }
    const linkAdd = "/cart_functions/" + id + "/" + val;
    const config = {
        method: 'PUT',
        baseURL: "https://compacttool.ru",
        url: linkAdd,
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' }
    };
    let res = await axios(config);
    //console.log(res);
    var a = res.data;
    const sumTotal = a.pop();
    document.getElementById("cartpopup").innerHTML = cartPopup(sumTotal, a); //Перерисуем корзину
    if (!document.querySelector("#order-items-list")) {
        const elem = document.querySelector('#del_' + id);
        elem.classList.add('vis_vis');
        elem.classList.remove('vis_hid');
    }
    document.getElementById("upcart").className = 'vis_vis';
    //Обновим корзину сверху
    document.getElementById("carttitle").setAttribute("title", sumTotal["tovarov"] + " " + morph(sumTotal["tovarov"]) + " на сумму " + sumTotal["total"] + "р");
    document.getElementById("upcart").innerText = sumTotal["tovarov"];
    // Обновим корзину если мы находимся в cart.php
    if (document.getElementById("cart_interface")) {
        document.getElementById("cart_interface").innerHTML = cartUpdate(sumTotal, a);
    }
}

//if(document.getElementById('signup') == null){ /// можно выполнять только если мы не на checkout.php
async function delFromCart(id) {
    const linkAdd = "/cart_functions/" + id;
    const config = {
        method: 'DELETE',
        baseURL: "https://compacttool.ru",
        url: linkAdd,
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' }
    };
    let res = await axios(config);//отправили на сервер данные что удлить
    var a = res.data;
    //console.log(res);
    const elem = document.querySelector('#del_' + id);
    if (elem) {
        elem.classList.remove('vis_vis');
        elem.classList.add('vis_hid');
    }
    if (a["tovarov"] != 0) { ///перерисовываем корзину
        const sumTotal = a.pop(); // отделяем сумму и колво товаров
        //Обновим корзину сверху
        document.getElementById("cartpopup").innerHTML = cartPopup(sumTotal, a);
        document.getElementById("upcart").innerText = sumTotal["tovarov"];//el.innerText = '1';
        document.getElementById("carttitle").setAttribute("title", sumTotal["tovarov"] + " " + morph(sumTotal["tovarov"]) + " на сумму " + sumTotal["total"] + "р");
        if (document.getElementById("cart_interface")) { /// если мы на странице cart.php и есть сей ид то и в нем надо обновить всё
            document.getElementById("cart_interface").innerHTML = cartUpdate(sumTotal, a);
        }
    } else {
        document.getElementById("upcart").className = 'vis_hid'; document.getElementById("carttitle").title = "Корзина пуста";
        document.getElementById("cartpopup").innerHTML = '<div class="text-center mt-5"><p>В корзине нет товаров</p></div><hr class="cart-popup__hrgray"/><div class="cart-popup__bottom"><a href="https://compacttool.ru/korzina/" class="btn btn-outline-success">В КОРЗИНУ</a></div>';
        if (document.getElementById("cart_interface")) { /// если мы на странице cart.php и есть сей ид то и в нем надо обновить всё
            document.getElementById("cart_interface").innerHTML = '<div class="col-12 border-top border-bottom text-center mt-5"><p>Похоже в корзине <strong>ничего</strong> нет! Что делать теперь ? <br>Начните с <a href="https://compacttool.ru/">главной</a> страницы  ! </p></div>';
        }
    }
}
async function eraseCart() {
    if (confirm("Очистить корзину, точно да ?")) {
        const config = {
            method: 'DELETE',
            baseURL: "https://compacttool.ru",
            url: "/cart_functions/erase",
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' }
        };
        let res = await axios(config);//очистить корзину
        var a = res.data;
        if (a) {
            a.forEach((item) => {
                if (document.getElementById('del_' + item)) {//если на странице есть товары которые мы удаляем
                    const elem = document.querySelector('#del_' + item);
                    elem.classList.remove('vis_vis');
                    elem.classList.add('vis_hid');
                }
            });
            document.getElementById("cartpopup").innerHTML = '<div class="text-center mt-5"><p>В корзине нет товаров</p></div><hr class="cart-popup__hrgray"/><div class="cart-popup__bottom"><button class="btn btn-outline-success">В КОРЗИНУ</button></div>';
            document.getElementById("upcart").className = 'vis_hid';
            if (document.getElementById("cart_interface")) { /// если мы на странице cart.php и есть сей ид то и в нем надо обновить всё
                document.getElementById("cart_interface").innerHTML = '<div class="col-12 border-top border-bottom text-center mt-5"><p>Похоже в корзине <strong>ничего</strong> нет! Что делать теперь ? <br>Начните с <a href="https://compacttool.ru/">главной</a> страницы  ! </p></div>';
            }
            if (document.getElementById('signup')) { //Если мы на страничке с оформлением заказа и решили корзину внезапно сбросить...переадресуем на пустую корзину...
                window.location.href = "https://" + window.location.hostname + "/korzina/";
            }
        }
    }  //Конец  точно надо очистить ???
}
//}/// КОНЕЦ ЕСЛИ ЭТО НЕ ЧЕКАУТ

function showpopup() {
    document.querySelector('#cartpopup').classList.add('cart-popup-show');
}
document.getElementById("carttitle").addEventListener('mouseover', showpopup);

function hidepopup() {
    window.menuTimeoutId = setTimeout(() => {

        document.querySelector('#cartpopup').classList.remove('cart-popup-show');


    }, 1500);

}
document.getElementById("carttitle").addEventListener('mouseout', hidepopup);



function showuser() {
    document.querySelector('#userpopup').classList.add('cart-popup-show');
}
if (document.getElementById("usertitle")) {
    document.getElementById("usertitle").addEventListener('mouseover', showuser);
}

function hideuser() {
    window.menuTimeoutId = setTimeout(() => {

        document.querySelector('#userpopup').classList.remove('cart-popup-show');


    }, 1000);

}
if (document.getElementById("usertitle")) {
    document.getElementById("usertitle").addEventListener('mouseout', hideuser);
}
async function addToLike(id, param) {
    const linkAdd = "/like_functions/" + id;
    const config = {
        method: 'PUT',
        baseURL: "https://compacttool.ru",
        url: linkAdd,
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' }
    };
    let res = await axios(config);
    //console.log(res.data);
    var a = res.data;
    if (/^(0|-?[1-9]\d{0,5})$/.test(a.code)) {
        param.classList.add('text-warning');
        param.setAttribute('title', 'Уже в избранном');
        param.removeAttribute("onclick");
        param.setAttribute("onclick", `delFromLike(${id}, this)`)
        const uplike = document.getElementById('uplike');
        uplike.innerHTML = a.code;
        if (a.code == 1) { uplike.classList.remove('vis_hid'); }
    } else if (a.code == "false") {
        param.classList.add('text-warning');
        param.setAttribute('title', 'Уже в избранном');
    }
}

async function delFromLike(id, param) {
    const linkAdd = "/like_functions/" + id;
    const config = {
        method: 'DELETE',
        baseURL: "https://compacttool.ru",
        url: linkAdd,
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' }
    };
    let res = await axios(config);
    //console.log(res.data);
    var a = res.data;
    if (/^(0|-?[1-9]\d{0,5})$/.test(a.code)) {
        param.classList.remove('text-warning');
        param.setAttribute('title', 'В избранное');
        param.removeAttribute("onclick");
        param.setAttribute("onclick", `addToLike(${id}, this)`)
        const uplike = document.getElementById('uplike');
        uplike.innerHTML = a.code;
        if (a.code == 0) { uplike.classList.add('vis_hid'); }
    }

}
function showPass() {
    var input = document.getElementById('userPass');
    var target = document.getElementById("showPass");
    if (input.getAttribute('type') == 'password') {
        target.classList.remove('icon-eye-blocked');
        target.classList.add('icon-eye');
        input.setAttribute('type', 'text');
    } else {
        target.classList.remove('icon-eye');
        target.classList.add('icon-eye-blocked');
        input.setAttribute('type', 'password');
    }
}
document.getElementById("showPass").addEventListener('click', showPass);

function nameChecking() {
    var name = document.getElementById("userName").value;
    if (name.length > 1) {
        if (/^[А-ЯЁ][а-яё]+$/.test(name) === false) {
            document.getElementById("nameLabel").classList.add("text-danger");
            var userInfo = document.getElementById("nameInfo");
            userInfo.classList.remove("d-none");
            userInfo.innerText = "Имя должно начинаться с заглавной буквы и допустима только кириллица";
            return false;
        }
        if (name.length > 20) {
            document.getElementById("nameLabel").classList.add("text-danger");
            var userInfo = document.getElementById("nameInfo");
            userInfo.classList.remove("d-none");
            userInfo.innerText = "В имени допустимо не более 20 символов, сорри...";
            return false;
        }

        document.getElementById("nameLabel").classList.remove("text-danger");
        document.getElementById("nameInfo").classList.add("d-none");
        return true;
    } else {
        document.getElementById("nameLabel").classList.remove("text-danger");
        document.getElementById("nameInfo").classList.add("d-none");
        return false;
    }
}
document.getElementById("userName").addEventListener('blur', nameChecking);

function lastChecking() {
    var last = document.getElementById("userLast").value;
    if (last.length > 1) {
        if (/^[А-ЯЁ][а-яё]+$/.test(last) === false) {
            document.getElementById("lastLabel").classList.add("text-danger");
            var userInfo = document.getElementById("lastInfo");
            userInfo.classList.remove("d-none");
            userInfo.innerText = "Фамилия должна начинаться с заглавной буквы и допустима только кириллица";
            return false;
        }
        if (last.length > 30) {
            document.getElementById("lastLabel").classList.add("text-danger");
            var userInfo = document.getElementById("lastInfo");
            userInfo.classList.remove("d-none");
            userInfo.innerText = "В фамилии допустимо не более 30 символов, сорри...";
            return false;
        }

        document.getElementById("lastLabel").classList.remove("text-danger");
        document.getElementById("lastInfo").classList.add("d-none");
        return true;
    } else {
        document.getElementById("lastLabel").classList.remove("text-danger");
        document.getElementById("lastInfo").classList.add("d-none");
        return false;
    }
}
document.getElementById("userLast").addEventListener('blur', lastChecking);

function emailChecking() {
    var email = document.getElementById("userEmail").value;
    if (email.length > 1) {
        if (/^[\w]{1}[\w-\.]*@[\w-]+\.[a-z]{2,4}$/i.test(email) === false) {
            document.getElementById("mailLabel").classList.add("text-danger");
            var userInfo = document.getElementById("mailInfo");
            userInfo.classList.remove("d-none");
            userInfo.innerText = "Вы ввели некорректный email нужен типа mail@mail.ru";
            return false;
        }
        document.getElementById("mailLabel").classList.remove("text-danger");
        document.getElementById("mailInfo").classList.add("d-none");
        return true;
    } else {
        document.getElementById("mailLabel").classList.remove("text-danger");
        document.getElementById("mailInfo").classList.add("d-none");
        return false;
    }
}
document.getElementById("userEmail").addEventListener('blur', emailChecking);

function passChecking() {
    var pass = document.getElementById("userPass").value;
    if (pass.length > 1) {
        if (pass.length < 8 || pass.length > 20) {
            document.getElementById("passLabel").classList.add("text-danger");
            var passInfo = document.getElementById("passInfo");
            passInfo.classList.remove("d-none");
            passInfo.innerText = "Пароль должен содержать от 8 до 20 символов";
            return false;
        }
        if (/^[\w!@#$%^&*-_]+$/i.test(pass) === false) {
            document.getElementById("passLabel").classList.add("text-danger");
            var passInfo = document.getElementById("passInfo");
            passInfo.classList.remove("d-none");
            passInfo.innerText = "Допустимы латинские буквы цифры и спец символы";
            return false;
        }
        document.getElementById("passLabel").classList.remove("text-danger");
        document.getElementById("passInfo").classList.add("d-none");
        return true;
    } else {
        document.getElementById("passLabel").classList.remove("text-danger");
        document.getElementById("passInfo").classList.add("d-none");
        return false;
    }
}
document.getElementById("userPass").addEventListener('blur', passChecking);

async function letReguser() {
    const userName = document.getElementById("userName").value;
    const userLast = document.getElementById("userLast").value;
    const userEmail = document.getElementById("userEmail").value;
    const userPass = document.getElementById("userPass").value;
    if (userName.length > 2 && userLast.length > 2 && userEmail.length > 6 && userPass.length > 4) {
        const config = {
            method: 'POST',
            baseURL: "https://compacttool.ru",
            url: "/login_functions/get_code",
            data: { username: userName, userlast: userLast, useremail: userEmail, userpass: userPass },
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' }
        };
        let res = await axios(config); //
        //console.log(res.data);
        if (res.data.code == "true") {  // Да такой телефон нам известен
            document.getElementById("modalCode").classList.remove("d-none");
            document.getElementById("modalReg").classList.add("d-none");
            //Шлем код и ыкидываем форму кода
        } else if (res.data.code == "fail") {
            document.getElementById("modalFail").classList.remove("d-none");
            document.getElementById("modalReg").classList.add("d-none");
            document.getElementById("textFail").innerHTML = res.data.message;
            window.setTimeout(function () {
                window.location.href = "https://compacttool.ru";
            }, 10000);
        } // тут выкидываем форму ошибки, что мы заблокировали возможность регистрации на пару часов

    }
}
document.getElementById("letReg").addEventListener('click', letReguser);


async function nextStep() {
    var phoneNum = document.getElementById("userPhone").value;
    if (/^((8|\+7)[\- ]?)?(\(?[9]{1}\d{2}\)?[\- ]?)[\- ]?[\d]{3}[\- ]?[\d]{2}[\- ]?[\d]{2}$/.test(phoneNum)) {
        const config = {
            method: 'POST',
            baseURL: "https://compacttool.ru",
            url: "/login_functions/check_phone",
            data: { phone: phoneNum },
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' }
        };
        let res = await axios(config);
        //console.log(res.data);
        if (res.data.code == "true") {
            document.getElementById("modalCode").classList.remove("d-none");
            document.getElementById("modalPhone").classList.add("d-none");
            document.getElementById("userCode").focus();
        } else if (res.data.code == "false") {
            document.getElementById("modalReg").classList.remove("d-none");
            document.getElementById("modalPhone").classList.add("d-none");
        } else if (res.data.code == "fail") {
            document.getElementById("modalFail").classList.remove("d-none");
            document.getElementById("modalPhone").classList.add("d-none");
            document.getElementById("textFail").innerHTML = res.data.message;
            window.setTimeout(function () {
                window.location.href = "https://compacttool.ru";
            }, 10000);
        }
    }
}
document.getElementById("nextStep").addEventListener('click', nextStep);




function phoneChecking() {
    var phone = this.value;
    if (phone.length > 1) {
        if (/^((8|\+7)[\- ]?)?(\(?[9]{1}\d{2}\)?[\- ]?)[\- ]?[\d]{3}[\- ]?[\d]{2}[\- ]?[\d]{2}$/.test(phone) === false) {
            document.getElementById("phoneLabel").classList.add("text-danger");
            var userInfo = document.getElementById("phoneInfo");
            userInfo.classList.remove("d-none");
            userInfo.innerText = "Нам нужен российски мобильный 11 цифр типа +79261234567";
            document.getElementById("nextStep").disabled = true;
            return false;
        }
        document.getElementById("phoneLabel").classList.remove("text-danger");
        document.getElementById("phoneInfo").classList.add("d-none");
        document.getElementById("nextStep").disabled = false;
        return true;
    } else {
        document.getElementById("phoneLabel").classList.remove("text-danger");
        document.getElementById("phoneInfo").classList.add("d-none");
        document.getElementById("nextStep").disabled = true;
    }
}
document.getElementById("userPhone").addEventListener('blur', phoneChecking);

async function codeChecking() {
    if (this.value.length == 4 && !isNaN(this.value)) {
        const config = {
            method: 'POST',
            baseURL: "https://compacttool.ru",
            url: "/login_functions/check_code",
            data: { code: this.value },
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' }
        };
        let res = await axios(config);
        //console.log(res.data);
        if (res.data.code == "true") {
            window.location = "/profil/";
        } else if (res.data.code == "fail") { //console.log(res.data);
            document.getElementById("modalFail").classList.remove("d-none");
            document.getElementById("modalCode").classList.add("d-none");
            document.getElementById("textFail").innerHTML = res.data.message;
            window.setTimeout(function () {
                window.location.href = "https://compacttool.ru";
            }, 10000);
        } else if (res.data.code == "false") {
            document.getElementById("userCode").value = "";
            document.getElementById("userCode").focus();
            document.getElementById("codeLabel").innerHTML = "Попробуйте снова";
        }
    }
}
document.getElementById("userCode").addEventListener('input', codeChecking);


function changePhone() {
    document.getElementById("modalPhone").classList.remove("d-none");
    document.getElementById("modalCode").classList.add("d-none");
    document.getElementById("userCode").value = "";
    document.getElementById("userPhone").value = "";
    document.getElementById("userPhone").focus();
}

document.getElementById("change_phone").addEventListener('click', changePhone);

function loginemailChecking() {
    var email = document.getElementById("loginEmail").value;
    if (email.length > 1) {
        if (/^[\w]{1}[\w-\.]*@[\w-]+\.[a-z]{2,4}$/i.test(email) === false) {
            document.getElementById("loginmailLabel").classList.add("text-danger");
            var userInfo = document.getElementById("loginmailInfo");
            userInfo.classList.remove("d-none");
            userInfo.innerText = "Вы ввели некорректный email нужен типа mail@mail.ru";
            return false;
        }
        document.getElementById("loginmailLabel").classList.remove("text-danger");
        document.getElementById("loginmailInfo").classList.add("d-none");
        return true;
    } else {
        document.getElementById("loginmailLabel").classList.remove("text-danger");
        document.getElementById("loginmailInfo").classList.add("d-none");
        return false;
    }
}
document.getElementById("loginEmail").addEventListener('blur', loginemailChecking);

function loginpassChecking() {
    var pass = document.getElementById("loginPass").value;
    if (pass.length > 1) {
        if (pass.length < 4 || pass.length > 20) {
            document.getElementById("loginpassLabel").classList.add("text-danger");
            var passInfo = document.getElementById("loginpassInfo");
            passInfo.classList.remove("d-none");
            passInfo.innerText = "Пароль должен содержать от 4 до 20 символов";
            return false;
        }
        if (/^[\w!@#$%^&*-_]+$/i.test(pass) === false) {
            document.getElementById("loginpassLabel").classList.add("text-danger");
            var passInfo = document.getElementById("loginpassInfo");
            passInfo.classList.remove("d-none");
            passInfo.innerText = "Допустимы латинские буквы цифры и спец символы";
            return false;
        }
        document.getElementById("loginpassLabel").classList.remove("text-danger");
        document.getElementById("loginpassInfo").classList.add("d-none");
        return true;
    } else {
        document.getElementById("loginpassLabel").classList.remove("text-danger");
        document.getElementById("loginpassInfo").classList.add("d-none");
        return false;
    }
}
document.getElementById("loginPass").addEventListener('blur', loginpassChecking);

function loginshowPass() {
    var input = document.getElementById('loginPass');
    var target = document.getElementById("loginshowPass");
    if (input.getAttribute('type') == 'password') {
        target.classList.remove('icon-eye-blocked');
        target.classList.add('icon-eye');
        input.setAttribute('type', 'text');
    } else {
        target.classList.remove('icon-eye');
        target.classList.add('icon-eye-blocked');
        input.setAttribute('type', 'password');
    }
}
document.getElementById("loginshowPass").addEventListener('click', loginshowPass);

async function letLog() {

    var loginEmail = document.getElementById("loginEmail").value;
    var loginPass = document.getElementById("loginPass").value;
    if (loginEmail.length > 4 && loginPass.length > 4 && loginPass.length < 20 && /^[\w]{1}[\w-\.]*@[\w-]+\.[a-z]{2,4}$/i.test(loginEmail) && /^[\w!@#$%^&*-_]+$/i.test(loginPass)) {
        const config = {
            method: 'POST',
            baseURL: "https://compacttool.ru",
            url: "/login_functions/login",
            data: { loginemail: loginEmail, loginpass: loginPass, uid: uidd },
            headers: { 'Content-Type': 'application/x-www-form-urlencoded' }
        };
        let res = await axios(config);
        console.log(res);
        if (res.data.code == "true") {
            window.location = "/profil/";
        } else if (res.data.code == "fail") {
            document.getElementById("modalFail").classList.remove("d-none");
            document.getElementById("modalEmail").classList.add("d-none");
            document.getElementById("textFail").innerHTML = res.data.message;
            window.setTimeout(function () {
                window.location.href = "https://compacttool.ru";
            }, 10000);
        }
    }
}
document.getElementById("letLog").addEventListener('click', letLog);

async function logOut() {
    const config = {
        method: 'GET',
        baseURL: "https://compacttool.ru",
        url: "/login_functions/logout",
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' }
    };
    let res = await axios(config); // логиним
    //console.log(res);
    if (res.data.code == "true") {
        location.replace("https://compacttool.ru")  ///Перезагрузка страницы
    }
}
if (document.getElementById("logOut")) {
    document.getElementById("logOut").addEventListener('click', logOut);
}
if (document.querySelector("#logOut2")) {
    document.querySelector("#logOut2").addEventListener('click', logOut);
}

document.getElementById("byEmail").addEventListener('click', function () {
    document.getElementById("modalEmail").classList.remove("d-none");
    document.getElementById("modalPhone").classList.add("d-none");
});
document.getElementById("byPhone").addEventListener('click', function () {
    document.getElementById("modalPhone").classList.remove("d-none");
    document.getElementById("modalEmail").classList.add("d-none");
});
const uidd = "doiy";

var toggleMenueCat = document.querySelectorAll(".cat_p");
for (let i = 0; i < toggleMenueCat.length; i++) {
    toggleMenueCat[i].addEventListener('click', function () {
        this.nextSibling.nextSibling.classList.toggle("show");
    });
}

//
///
///
// То что касается редактирования корзины cart.php
function updateCart(e, id) {
    var cartValue = e.value;
    if (cartValue < 1 || isNaN(cartValue)) { e.value = 1; cartValue = 1; }
    serverCart(id, cartValue);
};
async function serverCart(id, kol) {
    const linkAdd = "/cart_functions/" + id + "/" + kol;
    const config = {
        method: 'PATCH',
        baseURL: "https://compacttool.ru",
        url: linkAdd,
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' }
    };
    let res = await axios(config);//отправили на сервер данные что обновить
    //console.log(res.data);
    var a = res.data;
    if (a["tovarov"] != 0) { ///перерисовываем корзину
        const sumTotal = a.pop(); // отделяем сумму и колво товаров
        document.getElementById("cart_interface").innerHTML = cartUpdate(sumTotal, a);
    }
}
function cartUpdate(tovarov, arrayOfGoods) {
    var key = 1;
    var cartText = '<div class="col-12 d-none d-md-block fw-bold text-center pt-2" style="border-bottom:1px solid #00695c; height: 40px;"><div class="row"><div class="col-1">#</div><div class="col-1">Изобр.</div><div class="col-3">Название</div><div class="col-1">Артикул</div><div class="col-1">Цена р.</div><div class="col-2">Количество</div><div class="col-2">Сумма р.</div><div class="col-1">Удалить</div></div></div>';
    arrayOfGoods.forEach((goods) => { // рисуем корзину
        cartText += '<div class="col-12 border-bottom text-center cart_main pt-2"><div class="row"><div class="col-1 pt-4"><strong>' + (key++) + '</strong></div><div class="col-4 col-md-1"><a href="https://compacttool.ru/' + goods["chpu"] + '"><img src="https://cdn.compacttool.ru/images/min/' + goods['id'] + '_1.jpg" alt="' + goods["name"] + '" title="' + goods["name"] + '" class="cart_img_st"></a></div><div class="col-5 col-md-3 pt-lg-2"><p class="mb-0"><a href="https://compacttool.ru/' + goods["chpu"] + '">' + goods["name"] + '</a></p>' + (goods['kolvo'] == 0 ? '<p class="small text-danger">На данный момент этого товара нет на нашем складе.</p>' : '') + '</div><div class="col-2 col-md-1 pt-4"><span class="d-block d-md-none font-weight-bold">Арт.</span>' + goods['art'] + '</div><div class="col-2 col-md-1 pt-4 h6"><span class="d-block d-md-none font-weight-bold">Цена</span>' + goods['price'] + '</div><div class="col-5 col-md-2 pt-4"><div class="input-group input-group-sm justify-content-center" ><button class="btn border dec" type="button" onclick="decrement(' + goods['id'] + ')"><i class="bi bi-dash-lg"></i></button><input type="t/ext" onchange="updateCart(this,' + goods["id"] + ')" inputmode="numeric" maxlength="4" class="form-control" value="' + goods['tov_qty'] + '" style="max-width: 55px;" id="' + goods['id'] + '"><button class="btn border inc" type="button" onclick="increment(' + goods['id'] + ')"><i class="bi bi-plus-lg"></i></button></div></div><div class="col-3 col-md-2 pt-4 h6"><span class="d-block d-md-none fw-bold">Сумма</span>' + (goods["tov_qty"] * goods["price"]) + '</div><div class="col-1 pt-4"><i class="bi bi-trash cart_del_c" onclick="delFromCart(' + goods['id'] + ')" title="удалить"></i></div></div></div>';
    });
    cartText += '<div class="col-12 my-5"><div class="row"><div class="col-12 col-sm-6 col-lg-8 text-end"><span class="h4">Итог:</span><span class="h2"> ' + tovarov['total'] + '</span> <strong>руб.</strong></div><div class="col-12 col-sm-6 col-lg-4 "><a href="https://compacttool.ru/oformit-zakaz/" class="btn btn-outline-success float-right float-sm-none">ОФОРМИТЬ ЗАКАЗ <i class="bi bi-arrow-right-short"></i></a></div></div></div></div>';
    return cartText;
}

document.querySelector(".mainmnu").addEventListener('click', function () { document.querySelector(".lm").classList.toggle("show"); });
//document.querySelector(".mainmnu,.lm").addEventListener('mouseout', function () { document.querySelector(".lm").classList.remove("show"); });

document.getElementById('searchtext').oninput = function (e) {
    if (e.target.value.length > 2 && e.target.value.length < 60) {
        search(e.target.value);
    } else {
        document.getElementById('searchres').style.display = 'none';
    }
}
async function search(str) {
    const config = {
        method: 'POST',
        baseURL: "https://compacttool.ru",
        url: "/search/",
        data: { searchStr: str, save: uidd },
        headers: { 'Content-Type': 'application/x-www-form-urlencoded' }
    };
    let res = await axios(config);
    var a = res.data
    var srctext = '';
    if (a !== null) {
        a.forEach((goods) => {
            srctext += '<div class="col-12 col-sm-3"><a href="https://compacttool.ru/' + goods['chpu'] + '"><img src="https://cdn.compacttool.ru/images/min/' + goods["id"] + '_1.jpg" class="img-fluid"></a></div><div class="col-12 col-sm-9 d-flex align-items-center border-bottom"><a  href="https://compacttool.ru/' + goods['chpu'] + '">' + goods['name'] + '</a></div>';
        });
    } else {
        srctext += '<div  class="col-12 text-center">Не нашли ничего</div>';
    }
    document.getElementById('searchres').style.display = 'block';
    document.getElementById('searchres').innerHTML = '<div class="row" >' + srctext + '</div>';
}
//view.php only
if (document.getElementById('carousel-thumb')) {
    document.getElementById("togglediv").addEventListener('click', function (e) {
        if (e.target.id !== "starAdd") {
            var changed = document.getElementById("changed");
            var changedtoo = document.getElementById("changedtoo");
            if (changed.classList.contains("col-xl-4")) {
                changed.classList.remove("col-xl-4", "col-lg-5");
                changedtoo.classList.remove("col-xl-8", "col-lg-7");
                changed.classList.add("col-xxl-8", "offset-xxl-2", "col-xl-10", "offset-xl-1");
            } else {
                changed.classList.remove("col-xxl-8", "offset-xxl-2", "col-xl-10", "offset-xl-1");
                changed.classList.add("col-xl-4", "col-lg-5");
                changedtoo.classList.add("col-xl-8", "col-lg-7");
            }
        }
    });
    carousel_imgs = document.querySelectorAll(".carousel-item > img")
    carousel_imgs.forEach(carousel_img => {
        carousel_img.style.maxWidth = 1024 / window.devicePixelRatio + "px"
    });
}
// checkout.php only
if (document.getElementById('signup')) {
    new window.CDEKWidget({
        root: 'cdek-map',
        apiKey: '3ea5ae32-0947-40a6-9539-59722b5634a3',
        servicePath: '../js/sdek/service.php',
        defaultLocation: 'Москва',
        from: 'Москва',
        tariffs: {
            office: [136, 234],
            door: [137, 233],
            pickup: [368, 378],
        },
        dedug: true,
        goods: [
            {
                length: 30,
                width: 20,
                height: 40,
                weight: 3000,
            }],
        onChoose(type, tariff, address) {
            if (type === 'door') {
                document.querySelector('.sposob').innerHTML = "Курьерская доставка СДЭК";
                document.getElementById('dosttype').value = "Курьерская доставка СДЭК";
                document.querySelector('.detali').innerHTML = "Адрес: <u>" + address.formatted + "</u>";
                if (document.querySelector(".setaddr") !== null) { document.querySelector(".setaddr").remove(); }
                document.getElementById('phoneinput').insertAdjacentHTML('afterEnd', '<div class="input-group input-group-sm mt-2 setaddr"><span class="input-group-text bckform"><i class="icon-compass"></i></span><input type="text" name="adress" id="adress" class="form-control"  title="Адрес доставки" value="' + address.formatted + '" ></div>');
                if (tariff.period_max != null) {
                    document.querySelector(".time").classList.remove("d-none");
                    document.querySelector(".time").innerHTML = "<p><b>Время доставки:</b> <span>" + tariff.period_max + " дн.</span><span class='small'> (данные примерные)</span></p>";
                } else {
                    document.querySelector(".time").classList.add("d-none");
                }
                if (tariff.delivery_sum == null) {
                    document.querySelector(".cena").innerHTML = "Не смогли определить";
                } else {
                    document.querySelector(".cena").innerHTML = tariff.delivery_sum + " руб.";
                    var data = parseInt(document.querySelector('.itogo').dataset.sum) + parseInt(tariff.delivery_sum);
                    document.querySelector(".itogo").innerHTML = '<p class="h5"><b>ИТОГО: </b>' + data + ' р.</p>';
                }
                document.getElementById('dostprice').value = tariff.delivery_sum;
                document.getElementById('adress').insertAdjacentHTML('afterEnd', '<input type="text" name="flat" id="flat" required class="form-control" title="Квартира/офис/этаж" value="" placeholder="Квартира/офис/этаж*">');
            } else {
                //console.log(address);
                if (address.type == "POSTAMAT") {
                    document.querySelector('.sposob').innerHTML = "До постамата СДЕК";
                    document.getElementById('dosttype').value = "До постамата СДЕК";
                } else {
                    document.querySelector('.sposob').innerHTML = "До пункта выдачи СДЕК";
                    document.getElementById('dosttype').value = "До пункта выдачи СДЕК";
                }
                document.querySelector('.detali').innerHTML = "Доставка в город <u>" + address.city + "</u> по адресу <u>" + address.address + "</u>. Режим раоты: <u>" + address.work_time + "</u> ";
                if (document.querySelector(".setaddr") !== null) {
                    document.querySelector(".setaddr").remove();
                }
                document.getElementById('phoneinput').insertAdjacentHTML('afterEnd', '<div class="input-group input-group-sm mt-2 setaddr"><span class="input-group-text bckform"><i class="icon-compass"></i></span><input type="text" name="adress" id="adress" class="form-control"  title="Адрес доставки" value="' + address.city + ', ' + address.address + ', Режим работы:' + address.work_time + '" readonly ></div>');
                if (tariff.period_max != null) {
                    document.querySelector(".time").classList.remove("d-none");
                    document.querySelector(".time").innerHTML = "<p><b>Время доставки:</b> <span>" + tariff.period_max + " дн.</span><span class='small'> (данные примерные)</span></p>";
                }
                else {
                    document.querySelector(".time").classList.add("d-none");
                }
                if (tariff.delivery_sum == null) {
                    document.querySelector(".cena").innerHTML = "Не смогли определить";
                }
                else {
                    document.querySelector(".cena").innerHTML = tariff.delivery_sum + " руб.";
                    var data = parseInt(document.querySelector('.itogo').dataset.sum) + parseInt(tariff.delivery_sum);
                    document.querySelector(".itogo").innerHTML = '<p class="h5"><b>ИТОГО: </b>' + data + ' р.</p>';
                }
                document.getElementById('dostprice').value = tariff.delivery_sum;
            }
        },
    });
    //function cdekChoose(type, tariff, address)
    signup.onchange = function (e) {
        let lastnameInput = document.querySelector("#lastname")
        if (e.target.name == "delivery") {//пройдемся по доставкам
            if (e.target.value == 5) {//Самовывоз
                lastnameInput.required = false
                lastnameInput.placeholder = "Фамилия"
                document.getElementById('cdek-map').style = "position:absolute; left: -9999px;";
                document.querySelector('.sposob').innerHTML = "Самовывоз";
                document.querySelector('.detali').innerHTML = "Мы ждем Вас по адресу: г. Москва, Пятницкое шоссе, д. 18, 3 этаж, павильон 566 (согласно нашему режиму работы)";
                if (document.querySelector(".setaddr") !== null) {
                    document.querySelector(".setaddr").hidden = true
                    document.querySelector("#adress").disabled = true
                }
                document.querySelector(".time").classList.add("d-none");
                document.querySelector(".cena").innerHTML = "Бесплатно";
                var data = document.querySelector('.itogo').dataset.sum;
                document.querySelector(".itogo").innerHTML = '<p class="h5"><b>ИТОГО: </b>' + data + ' р.</p>';
                document.getElementById('dosttype').value = "Самовывоз";
                document.getElementById('dostprice').value = 0;
            }
            if (e.target.value == 6) {//Доставка курьром
                lastnameInput.required = false
                lastnameInput.placeholder = "Фамилия"
                document.getElementById('cdek-map').style = "position:absolute; left: -9999px;";
                document.querySelector('.sposob').innerHTML = "Курьером по г. Москва";
                document.querySelector('.detali').innerHTML = '<font color="red">Заполните поле адреса доставки !</font>';
                if (document.querySelector(".setaddr") !== null) {
                    document.querySelector("#adress").value = ""
                    document.querySelector(".setaddr").hidden = false
                    document.querySelector(".setaddr").readnly = false
                    document.querySelector("#adress").disabled = false
                    document.querySelector("#adress").required = true
                    document.querySelector("#adress").placeholder = "Введите адрес доставки*";
                }
                document.getElementById("adress").oninput = function () {
                    if (document.getElementById("adress").value.length > 0) {
                        document.querySelector('.detali').innerHTML = document.getElementById("adress").value;
                    } else {
                        document.querySelector('.detali').innerHTML = '<font color="red">Заполните поле адреса доставки !</font>';
                    }
                };
                document.querySelector(".time").classList.add("d-none");
                document.querySelector(".cena").innerHTML = "450 р.";
                var data = document.querySelector('.itogo').dataset.sum;
                document.querySelector(".itogo").innerHTML = '<p class="h5"><b>ИТОГО: </b>' + (parseInt(data) + 450) + ' р.</p>';
                document.getElementById('dosttype').value = "Курьером по г. Москва";
                document.getElementById('dostprice').value = 450;
            }
            if (e.target.value == 7) {//СДЭК
                document.getElementById('cdek-map').style = "";
                document.querySelector('.sposob').innerHTML = "До пункта выдачи СДЕК";
                document.getElementById('dosttype').value = "До пункта выдачи СДЕК";
                document.querySelector('.detali').innerHTML = '<font color="red">Выберите пункт выдачи или постамат</font>';
                lastnameInput.required = true
                lastnameInput.placeholder = "Фамилия*"
                if (document.querySelector(".setaddr") !== null) {
                    document.querySelector("#adress").value = ""
                    document.querySelector("#adress").placeholder = "Дождитесь загрузки карты и выберите доставку"
                    document.querySelector(".setaddr").hidden = false
                    document.querySelector("#adress").disabled = true
                }
            }
        }
        else if (e.target.name == "payment") {//пройдемся по доставкам
            if (e.target.value == 8) {//Нал
                document.getElementById('nds').disabled = true;
                document.querySelector('.oplata').innerHTML = '<p><b>Расчет:</b> Наличными при получении</p>';
                if (document.querySelector('#fieldsetCompany')) {
                    document.querySelector("#fieldsetCompany").hidden = true
                    document.querySelector("#companyDetails").disabled = true
                }
            }
            if (e.target.value == 9) {//Счет на оплату
                if (document.getElementById('nds').checked) {
                    document.querySelector('.oplata').innerHTML = '<p><b>Расчет:</b> Мы пришлем счет на оплату c НДС</p>';
                } else {
                    document.querySelector('.oplata').innerHTML = '<p><b>Расчет:</b> Мы пришлем счет на оплату без НДС</p>';
                }
                document.getElementById('nds').disabled = false;
                if (document.querySelector('#fieldsetCompany')) {
                    document.querySelector("#fieldsetCompany").hidden = false
                    document.querySelector("#companyDetails").disabled = false
                }
            }
            if (e.target.value == 11) {//Картой онлайн
                document.getElementById('nds').disabled = true;
                document.querySelector('.oplata').innerHTML = '<p><b>Расчет:</b> Картой онлайн после комплектации</p>';
                if (document.querySelector('#fieldsetCompany')) {
                    document.querySelector("#fieldsetCompany").hidden = true
                    document.querySelector("#companyDetails").disabled = true
                }
            }
            if (e.target.value == 10) {//Оплата по QR
                document.getElementById('nds').disabled = true;
                document.querySelector('.oplata').innerHTML = '<p><b>Расчет:</b> Мы пришлем QR код</p>';
                if (document.querySelector('#fieldsetCompany')) {
                    document.querySelector("#fieldsetCompany").hidden = true
                    document.querySelector("#companyDetails").disabled = true
                }
            }
        }
        document.getElementById('nds').onchange = function (nds) {
            document.getElementById('nds').checked ? document.querySelector('.oplata').innerHTML = '<p><b>Расчет:</b> Мы пришлем счет на оплату c НДС</p>' : document.querySelector('.oplata').innerHTML = '<p><b>Расчет:</b> Мы пришлем счет на оплату без НДС</p>';
        }
    }
    const forms = document.querySelectorAll('#name,#phone,#email');
    if (forms[0].value.length > 1 && forms[1].value.length > 6 && forms[2].value.length > 5) {
        document.getElementById('submit').disabled = false;
    }
    forms.forEach(r => {
        r.oninput = function () {
            if (forms[0].value.length > 1 && forms[1].value.length > 6 && forms[2].value.length > 5) {
                document.getElementById('submit').disabled = false;
            }
        }
    });
    document.getElementById('signup').onsubmit = function () {
        document.getElementById('slova').value = 'saveoursols';
        this.disabled = true;
    }

}///ЕСЛИ ЕСТЬ ФОРМА


// zakaz page script

// checked for the presence of elements
if (document.querySelector("#hidePhotosInOrder") && document.querySelector("#repeatOrder")) {

    function togglePhotosVisibility(toggleVisibility) {
        // checked current state
        if (toggleVisibility.isPhotoVisible) {
            // added necessary class for elements
            toggleVisibility.photoElements.forEach(photoElement => {
                photoElement.classList.add("d-none")
            });

            // added necessary class for elements
            toggleVisibility.nameElements.forEach(nameElement => {
                nameElement.classList.add("col-12")
            })

            // changed current state
            toggleVisibility.isPhotoVisible = false
            localStorage.setItem("photosVisibility", toggleVisibility.isPhotoVisible)
        } else {
            // added necessary class for elements
            toggleVisibility.photoElements.forEach(photoElement => {
                photoElement.classList.remove("d-none")
            });

            // added necessary class for elements
            toggleVisibility.nameElements.forEach(nameElement => {
                nameElement.classList.remove("col-12")
            })

            // changed current state
            toggleVisibility.isPhotoVisible = true
            localStorage.setItem("photosVisibility", toggleVisibility.isPhotoVisible)
        }
    }

    // selected buttons, list and create logical variable for save current state
    const hidePhotosButton = document.querySelector("#hidePhotosInOrder")
    const repeatOrderButton = document.querySelector("#repeatOrder")
    const itemsList = document.querySelector("#order-items-list")

    // selected all elements for show and hide
    const photoElements = itemsList.querySelectorAll("#order-photo")
    const nameElements = itemsList.querySelectorAll("#order-name")

    let isPhotoVisible = true

    toggleVisibility = { isPhotoVisible, photoElements, nameElements }

    if (localStorage.getItem("photosVisibility") == "false") {
        togglePhotosVisibility(toggleVisibility)
    } else {
        localStorage.setItem("photosVisibility", toggleVisibility.isPhotoVisible)
    }

    window.addEventListener('storage', (e) => {
        if (e.key == 'photosVisibility' && toggleVisibility.isPhotoVisible != JSON.parse(e.newValue)) {
            togglePhotosVisibility(toggleVisibility)
        }
    })

    // added listener for click on button
    hidePhotosButton.addEventListener("click", () => { togglePhotosVisibility(toggleVisibility) });

    // add listener for click on button
    repeatOrderButton.addEventListener("click", e => {
        const inputElements = document.querySelectorAll("input[data-good-id]")
        inputElements.forEach(inputElement => {
            addToCart(inputElement.id)
        });
    })
}
// profil page
if (document.querySelector("#addCompanyModal")) {
    function getCompanyDataByINN(dataForm) {
        const INN = dataForm.elements.inn
        axios.post('https://suggestions.dadata.ru/suggestions/api/4_1/rs/findById/party', {
            "query": dataForm.elements.INN.value
        }, {
            headers: {
                "Authorization": "Token 8b67dc553b9b897818cadba432aa6e02779b5705"
            }
        })
            .then(function (response) {
                if (response.data.suggestions.length != 0) {
                    dataForm.elements.name.value = response.data.suggestions[0].value
                    dataForm.elements.KPP.value = response.data.suggestions[0].data.kpp
                    dataForm.elements.address.value = response.data.suggestions[0].data.address.unrestricted_value
                }
            })
    }


    // Bootstrap validation
    // Fetch all the forms we want to apply custom Bootstrap validation styles to
    var forms = document.getElementsByClassName('needs-validation');
    // Loop over them and prevent submission
    var validation = Array.prototype.filter.call(forms, function (form) {
        form.addEventListener('submit', function (event) {
            if (form.checkValidity() === false) {
                event.preventDefault();
                event.stopPropagation();
            }
            form.classList.add('was-validated');
        }, false);
    });

    const dataForm = document.forms.data
    dataForm.elements.INN.addEventListener("input", () => {
        if (dataForm.elements.INN.value.length == 10 || dataForm.elements.INN.value.length == 12) {
            getCompanyDataByINN(dataForm)
        }
    })
    // mask inputs
    const element = document.getElementById('changeTelInput');
    const maskOptions = {
        mask: '+{7}(000)000-00-00',
        lazy: false,
    };
    const phoneInputModal = IMask(element, maskOptions);
    // end mask inputs

    function newToast(bodyText, colorScheme = null, autoHide = true) {
        const id = "F" + Math.random().toString(16).substring(2, 8)
        const htmlToast = `<div id="${id}" class="toast ${colorScheme ?? ''}" data-bs-delay="30000" ${autoHide ? "" : "data-bs-autohide='false'"} role="alert" aria-live="assertive" aria-atomic="true">
                        <div class="d-flex">
                            <div class="toast-body">${bodyText}</div>
                            <button type="button" class="btn-close me-2 m-auto" data-bs-dismiss="toast" aria-label="Close"></button>
                        </div>
                    </div>`;
        toastContainer = document.querySelector(".toast-container")
        toastContainer.insertAdjacentHTML("beforeend", htmlToast)
        const toastBootstrap = bootstrap.Toast.getOrCreateInstance(document.querySelector(`#${id}`))
        toastBootstrap.show()

        document.querySelector(`#${id}`).addEventListener('hidden.bs.toast', (event) => {
            event.target.remove()
        })
    }
    const confirmationEmailForm = document.forms.confirmationEmailForm
    const confirmationEmailModal = new bootstrap.Modal('#confirmationEmailModal')
    confirmationEmailForm.addEventListener('submit', event => {
        event.preventDefault()
        if (confirmationEmailForm.checkValidity()) {
            confirmationEmailForm.elements.submit.disabled = true;
            axios.post("/mail_confirmation/", new FormData(confirmationEmailForm))
                .then(function (response) {
                    if (response.status == 201) {
                        newToast("Вам было отправлено письмо, для подтверждения почты", "text-bg-primary")
                    }
                })
                .catch(function (error) {
                    if (error.response.status == 429) {
                        newToast("Письмо подтверждения можно отправлять не чаще раза в минуту", "text-bg-warning")
                    } else {
                        newToast("Возникла непредвиденная ошибка, обратитесь к администратору", "text-bd-danger")
                    }
                })
                .finally(function () {
                    confirmationEmailModal.hide()
                    confirmationEmailForm.elements.submit.disabled = false;
                })
        }
    })

    const changeEmailForm = document.forms.changeEmailForm
    const changeEmailModal = new bootstrap.Modal('#changeEmailModal')
    changeEmailForm.addEventListener('submit', event => {
        event.preventDefault()
        if (changeEmailForm.checkValidity()) {
            changeEmailForm.elements.submit.disabled = true
            axios.post("/mail_confirmation/", new FormData(changeEmailForm))
                .then(function (response) {
                    if (response.status == 201) {
                        newToast("Вам было отправлено письмо, для смены почты", "text-bg-primary")
                    } else {
                        newToast("Возникла непредвиденная ошибка, обратитесь к администратору", "text-bd-danger")
                    }
                })
                .catch(function (error) {
                    if (error.response.status == 429) {
                        newToast("Письмо подтверждения можно отправлять не чаще раза в минуту", "text-bg-warning")
                    } else {
                        newToast("Возникла непредвиденная ошибка, обратитесь к администратору", "text-bd-danger")
                    }
                })
                .finally(function () {
                    changeEmailModal.hide()
                    changeEmailForm.elements.emailFormSubmit.disabled = false;
                })
        }
    })

    const changePhoneForm = document.forms.changeTelForm
    const enterSmsCodeForm = document.forms.smsCodeInputForm

    const changePhoneModal = new bootstrap.Modal('#changePhone')
    const enterSmsCodeModal = new bootstrap.Modal('#smsCodeModal')

    const phoneSendSpan = enterSmsCodeModal._element.querySelector('.phoneSend')
    changePhoneForm.addEventListener('submit', event => {
        event.preventDefault()
        if (changePhoneForm.checkValidity()) {
            changePhoneForm.elements.submit.disabled = true
            phone = phoneInputModal.unmaskedValue
            axios.post("/login_functions/changePhone", { changePhone: phone })
                .then(function (response) {
                    if (response.status == 201) {
                        phoneSendSpan.innerText = phone
                        changePhoneModal.hide()
                        enterSmsCodeModal.show()
                    } else {
                        newToast("Возникла непредвиденная ошибка, обратитесь к администратору", "text-bd-danger")
                    }
                })
                .catch(function (error) {
                    if (error.response.data["code"] == 85463) {
                        newToast("Данный телефон уже привязан к акканту", "text-bg-warning")
                    } else if (error.response.data["code"] == 23845) {
                        newToast("Смс код можно отправить раз в минуту")
                    } else {
                        newToast("Возникла непредвиденная ошибка, обратитесь к администратору", "text-bd-danger")
                    }
                })
                .finally(function () {
                    changePhoneForm.elements.submit.disabled = false
                })
        }
    })

    enterSmsCodeForm.addEventListener('submit', event => {
        event.preventDefault()
        if (enterSmsCodeForm.checkValidity()) {
            if (enterSmsCodeForm.checkValidity()) {
                enterSmsCodeForm.elements.submit.disabled = true
                code = enterSmsCodeForm.elements.smsCode.value
                axios.post("/login_functions/changePhone", { changePhone: phone, code: code })
                    .then(function (response) {
                        if (response.status == 201) {
                            location.reload();
                        } else {
                            newToast("Возникла непредвиденная ошибка, обратитесь к администратору", "text-bd-danger")
                        }
                    })
                    .catch(function (error) {
                        newToast("Возникла непредвиденная ошибка, обратитесь к администратору", "text-bd-danger")
                    })
                    .finally(function () {
                        enterSmsCodeForm.elements.submit.disabled = false
                    })
            }
        }
    })

    const changePhoneButton = document.querySelector(".smsCodeModal__change-phone")
    changePhoneButton.addEventListener("click", event => {
        enterSmsCodeModal.hide()
        changePhoneModal.show()
    })
}

