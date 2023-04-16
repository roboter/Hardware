//refresh verify code in regist page
$(document).ready(function () {
    //初始加载验证码图片
    $("#checkpic").attr('src', 'checkcode.php?radom=' + Math.ceil(Math.random() * 100000));

    //点击刷新验证码图片
    $("#changepic").click(function () {
        $("#checkpic").attr('src', 'checkcode.php?radom=' + Math.ceil(Math.random() * 100000));
    });

});

$(document).ready(function () {
    //鼠标放在产品页的wholesale price上出现提示
    $("#wholesale_price").mouseover(function () {
        $("#wholesale_notice").css({
            'display': 'block'
        });
    });

    $("#wholesale_price").mouseout(function () {
        $("#wholesale_notice").css({
            'display': 'none'
        });
    });
});

//验证字段是否为空函数
function checkString(obj, name) {
    if (obj.val().length < 2) {
        alert(name + ' is required!');
        obj.focus();
        return false;
    } else return true;
}

//affiliate active account
$(document).ready(function () {
    $("#active").click(function () {
        var name = $("input[name=firstname]").val();
        var email = $("input[name=email_address]").val();
        if (!checkString($("input[name=firstname]"), 'firstname')) {
            return false;
        }
        ;
        $.get('myaffiliate.php?action=active&contact_name=' + name + "&email=" + email, function (rel) {
            if (rel == 1) {
                window.location.href = "myaffiliate.php";
            } else {
                alert('Active account faild,please try again!');
            }
        });
    });
});

//提交产品ID时，显示下面的隐藏框
$(document).ready(function () {
    $('.aff_btn').click(function () {
        $(this).siblings('.aff_show').css(
            'display', 'block'
        );
    });
});

//for newsletter subscribe
$(document).ready(function () {
    $('.show_more').click(function () {
        var text = $(this).html();
        //alert(text);
        if (text == "more") {
            $(this).html('less');
            $('.check_box').css({
                'display': 'block'
            });
        } else {
            $(this).html('more');
            $('.check_box').css({
                'display': 'none'
            });
        }
    });

    var length = $('.check_box input').size();
    //alert(length);
    $(".promotiontype").attr("checked", 'checked');
    $("input[name=newsletter]").click(function () {
        $(".promotiontype").attr("checked", this.checked);
    });
    $(".promotiontype").click(function () {
        $("input[name=newsletter]").attr("checked", length == $(".promotiontype:checked").length ? "checked" : false);
    });
});
//for reviews
$(document).ready(
    function () {
        $('#star-rating').mousemove(function (e) {
            var star = Math.floor((e.clientX - $(this).offset().left) / 20 + 1);
            $(this).attr({'class': 'star_' + star});
        }).mouseout(function (e) {
            var cl = $(this).attr('class');
            $(this).attr({'class': 'star_' + $('#rating').val()});
        }).click(function (e) {
            var star = Math.floor((e.clientX - $(this).offset().left) / 20 + 1);
            $('#rating').val(star);
            $(this).attr({'class': 'star_' + star});
        });
    });

//for botton
$(document).ready(
    function () {
        $("#search_field").focus(function () {
            if (this.value == "I'm looking for......") this.value = '';
        });
        $("#search_field").blur(function () {
            if (this.value == "") this.value = "I'm looking for......";
        });

        $("#subscr_field").focus(function () {
            if (this.value == "Enter your Email here") this.value = '';
        });
        $("#subscr_field").blur(function () {
            if (this.value == "") this.value = 'Enter your Email here';
        });

        $(".tdbLink").hover(
            function () {
                $(this).removeClass("tdbLink");
                $(this).addClass("tdbLinkOver");
            },
            function () {
                $(this).removeClass("tdbLinkOver");
                $(this).addClass("tdbLink");
            }
        );
        $(".tdbLink2").hover(
            function () {
                $(this).removeClass("tdbLink2");
                $(this).addClass("tdbLinkOver2");
            },
            function () {
                $(this).removeClass("tdbLinkOver2");
                $(this).addClass("tdbLink2");
            }
        );

        // $('#cart_box').hover(
        //     function () {
        //         $(this).find('.cart_content').show();
        //         $(this).find('.cart_till').addClass('cart_tillover')
        //     },
        //     function () {
        //         $(this).find('.cart_content').hide();
        //         $(this).find('.cart_till').removeClass('cart_tillover')
        //     }
        // );

        $("#main_catalog > ul > li").hover(
            function () {
                $(this).find('.sub_1').slideDown("fast");
            },
            function () {
                $(this).find('.sub_1').hide()
            }
        );
        $(".sub_1 > li").hover(
            function () {
                $(this).find('.sub_2').slideDown("fast");
                $(this).parent().prev().prev().addClass('menu_hover')
            },
            function () {
                $(this).find('.sub_2').hide();
                $(this).parent().prev().prev().removeClass('menu_hover')
            }
        )
        $(".sub_2 > li").hover(
            function () {
                $(this).find('.sub_2').slideDown("fast");
                $(this).parent().prev().prev().addClass('menu_hover')
            },
            function () {
                $(this).find('.sub_2').hide();
                $(this).parent().prev().prev().removeClass('menu_hover')
            }
        )

        $(".drop_downmen").hover(
            function () {
                $(this).find('#main_catalog').slideDown();
                $(this).find('#cabox').slideDown();
                $(this).find('#catalog_menu3').slideDown();
                $(this).find('.arrow').addClass('arrow_over')
            },
            function () {
                $(this).find('#main_catalog').hide();
                $(this).find('#cabox').hide();
                $(this).find('#catalog_menu3').hide();
                $(this).find('.arrow').removeClass('arrow_over')
            }
        )

        /*menu	*/
        $(".menu3w").parent().parent().addClass('menu3w');
        $(".menu3ww").parent().parent().addClass('menu3ww');

        $(".menu3_havsub").hover(
            function () {
                $(this).find('.menu3_submenu').show();
                $(this).addClass('menu3_menu_over');
                $(function () {
                    var $container = $('.masonry');
                    $container.imagesLoaded(function () {
                        $container.masonry({
                            itemSelector: '.menu3items'
                        });
                    });
                });
            },
            function () {
                $(this).find('.menu3_submenu').hide();
                $(this).removeClass('menu3_menu_over');
            }
        );


        /*menu end	*/
    });

//for wishlist
$(document).ready(
    function () {
        var products_id = $('#cart_quantity :input[name=products_id]').val();
        $("#ad_wishlist").click(function () {
            $.ajax({
                type: "POST",
                url: "checkout/Ajax_buynow.php?action=add_wishlist&products_id=" + products_id,
                data: $('#cart_quantity :input'),
                timeout: 10000,
                beforeSend: function () {
                },
                complete: function () {
                },
                error: function () {
                    alert('time out try again')
                },
                success: function (msg) {
                    var update_msg = msg.split("|");
                    if (update_msg[0] == '1') {
                        $("#message_ear").removeClass("Error");
                        $("#message_ear").addClass('Success')
                        $("#message_ear").html(update_msg[1]);
                        $("#message_ear").slideDown('slow');
                    }
                    else {
                        $("#message_ear").removeClass("Success");
                        $("#message_ear").addClass('Error')
                        $("#message_ear").html(update_msg[1]);
                        $("#message_ear").slideDown('slow');
                    }
                }//end success
            });//end ajax
        })
    }
);


function downbox(id) {
    if ($('#' + id + '').is(":hidden"))
        $('#' + id + '').slideDown("slow");
    else
        $('#' + id + '').slideUp("slow");
}

//for list type
function clt(type) {
    if (type == 'g') {
        $.ajax({
            type: "GET",
            url: "checkout/Ajax_buynow.php",
            data: "list_type=gride",
            timeout: 10000,
            beforeSend: function () {
            },
            complete: function () {
            },
            error: function () {
                alert('time out try again')
            },
            success: function () {
                $("#plist_ear").find("p").removeClass("list_iteml");
                $("#plist_ear").find("p").addClass("list_itemg");
                $("#gicon").removeClass("goff");
                $("#gicon").addClass("gon");
                if ($.browser.msie && ($.browser.version == "6.0") && !$.support.style) {
                    window.location.reload();
                }
            }
        })
    }
    else if (type == 'l') {
        $.ajax({
            type: "GET",
            url: "checkout/Ajax_buynow.php",
            data: "list_type=line",
            timeout: 10000,
            beforeSend: function () {
            },
            complete: function () {
            },
            error: function () {
                alert('time out try again')
            },
            success: function () {
                $("#plist_ear").find("p").removeClass("list_itemg");
                $("#plist_ear").find("p").addClass("list_iteml");
                $("#gicon").removeClass("gon");
                $("#gicon").addClass("goff");
                if ($.browser.msie && ($.browser.version == "6.0") && !$.support.style) {
                    window.location.reload();
                }
            }
        })
    }
}

//list

//for buynow bottom
$(document).ready(
    function () {
        $(".list_buynow1, .list_buynow2").click(
            function () {
                var products_id = ($(this).attr("id")).substr(1);
                var list_img = $(this).parent().parent().parent().find("img");

                var image_position = list_img.position(); //relative list item<br />
                var image_absolute_position = list_img.offset(); //relative list item
                var cart_position = $('#cart_position').offset();
                if (!cart_position) {
                    cart_position = $('#cart_number').offset();
                    cart_position.top = cart_position.top;
                    cart_position.left = cart_position.left - 150;
                }

                $(this).parent().parent().before('<img src="' + list_img.attr('src') + '" id="cart_tempimg" style="position: absolute; z-index:1000; border:1px solid #ff6600; top: ' + (image_position.top) + 'px; left: ' + image_position.left + 'px;" />');
                $.ajax({
                    type: "POST",
                    url: "checkout/Ajax_buynow.php",
                    data: "action=buy_now&products_id=" + products_id,
                    timeout: 10000,
                    beforeSend: function () {
                    },
                    complete: function () {
                    },
                    error: function () {
                        alert('time out try again')
                    },
                    success: function (msg) {
                        if (msg == 'NO') {
                            window.location.href = 'product_info.php?products_id=' + products_id;
                        }
                        else if (msg == 'Faild') {
                            $("#message_ear").removeClass("Success");
                            $("#message_ear").addClass('Error');
                            $("#message_ear").html('You can not choice free gift now.');
                            $("#message_ear").slideDown('slow');
                        }
                        else {
                            if (cart_position) {
                                params = {
                                    top: (cart_position.top - image_absolute_position.top + 10) + 'px',
                                    left: (cart_position.left - image_absolute_position.left + 10) + 'px',
                                    opacity: 0.5,
                                    width: '30px',
                                    height: '30px'
                                };
                                $('html, body').animate({scrollTop: 0}, 'slow', false, function () {
                                    $('#cart_tempimg').animate(params, 1000, false, function () {
                                        var update_msg = msg.split("|");
                                        $('#cart_number').html(update_msg[0]);
                                        $('#bm_shopping_cart').html(update_msg[1]);
                                        $('#cart_tempimg').remove();
                                        $("#message_ear").removeClass("Error");
                                        $("#message_ear").addClass('Success')
                                        $("#message_ear").html(update_msg[2]);
                                        $("#message_ear").slideDown('slow');
                                    });
                                });
                            }
                            else {
                                window.location.href = 'shopping_cart.php';
                            }
                        }
                    }
                })
            })
    })

//products add cart
function add_cart() {
    if (verify_attrib()) {
        var cart_position = $('#cart_position').offset();
        if (!cart_position) {
            cart_position = $('#cart_number').offset();
            cart_position.top = cart_position.top;
            cart_position.left = cart_position.left - 150;
        }
        var image_position = $('#Default_Image').position(); //relative
        var image_absolute_position = $('#Default_Image').offset(); //absolute list item
        $.ajax({
            type: "POST",
            url: "checkout/Ajax_buynow.php?action=add_cart",
            data: $('#cart_quantity').serialize(),
            timeout: 10000,
            beforeSend: function () {
            },
            complete: function () {
            },
            error: function () {
                alert('time out try again')
            },
            success: function (msg) {
                if (msg == 'Faild') {
                    $("#message_ear").removeClass("Success");
                    $("#message_ear").addClass('Error');
                    $("#message_ear").html('You can not choice free gift now.');
                    $("#message_ear").slideDown('slow');
                }
                else {
                    if (cart_position) {
                        $('#Default_Image').before('<img src="' + $('#Default_Image').attr('src') + '" id="cart_tempimg" style="position: absolute; z-index:1000; border:1px solid #ff6600; top: ' + (image_position.top) + 'px; left: ' + image_position.left + 'px;" />');
                        params = {
                            top: (cart_position.top - image_absolute_position.top + 10) + 'px',
                            left: (cart_position.left - image_absolute_position.left + 10) + 'px',
                            opacity: 0.5,
                            width: '30px',
                            height: '30px'
                        };
                        $('html, body').animate({scrollTop: 0}, 'slow', false, function () {
                            $('#cart_tempimg').animate(params, 1000, false, function () {
                                var update_msg = msg.split("|");
                                $('#cart_number').html(update_msg[0]);
                                $('#bm_shopping_cart').html(update_msg[1]);
                                $('#cart_tempimg').remove();
                                $("#message_ear").removeClass("Error");
                                $("#message_ear").addClass('Success')
                                $("#message_ear").html(update_msg[2]);
                                $("#message_ear").slideDown('slow');
                            });
                        });

                    } else {
                        window.location.href = 'shopping_cart.php';
                    }
                }
            }//end success
        });//end ajax
    }
}

//buy express
function buy_express() {
    if (verify_attrib()) {
        var cart_position = $('#cart_position').offset();
        if (!cart_position) {
            cart_position = $('#cart_number').offset();
            cart_position.top = cart_position.top;
            cart_position.left = cart_position.left - 150;
        }
        var image_position = $('#Default_Image').position(); //relative
        var image_absolute_position = $('#Default_Image').offset(); //absolute list item
        $.ajax({
            type: "POST",
            url: "checkout/Ajax_buynow.php?action=add_cart",
            data: $('#cart_quantity').serialize(),
            timeout: 10000,
            beforeSend: function () {
            },
            complete: function () {
            },
            error: function () {
                alert('time out try again')
            },
            success: function (msg) {
                if (msg == 'Faild') {
                    $("#message_ear").removeClass("Success");
                    $("#message_ear").addClass('Error');
                    $("#message_ear").html('You can not choice free gift now.');
                    $("#message_ear").slideDown('slow');
                }
                else {
                    if (cart_position) {
                        $('#Default_Image').before('<img src="' + $('#Default_Image').attr('src') + '" id="cart_tempimg" style="position: absolute; z-index:1000; border:1px solid #ff6600; top: ' + (image_position.top) + 'px; left: ' + image_position.left + 'px;" />');
                        params = {
                            top: (cart_position.top - image_absolute_position.top + 10) + 'px',
                            left: (cart_position.left - image_absolute_position.left + 10) + 'px',
                            opacity: 0.5,
                            width: '30px',
                            height: '30px'
                        };
                        $('html, body').animate({scrollTop: 0}, 'slow', false, function () {
                            $('#cart_tempimg').animate(params, 1000, false, function () {
                                var update_msg = msg.split("|");
                                $('#cart_number').html(update_msg[0]);
                                $('#bm_shopping_cart').html(update_msg[1]);
                                $('#cart_tempimg').remove();
                                $("#message_ear").removeClass("Error");
                                $("#message_ear").addClass('Success')
                                $("#message_ear").html(update_msg[2]);
                                $("#message_ear").slideDown('slow');
                            });
                        });
                        window.location.href = 'shopping_cart.php';
                    } else {
                        window.location.href = 'shopping_cart.php';
                    }
                }
            }//end success
        });//end ajax
    }
}

function changeImage(imageNumber) {
    $('#Default_Image').fadeOut("fast", function () {
        $('#Default_Image').attr("src", "images/middle/" + imageNumber);
        $('#thumb0').attr("href", "images/big/" + imageNumber);
        $('#Default_Image').fadeIn("fast");
    });
}

function addtab(id, actions) {
    var tabContainers = $("#" + id + "> div");
    if (actions == 'click') {
        $('#' + id + ' ul.tabNavigation a').click(function () {
            tabContainers.hide().filter(this.hash).show();
            $('#' + id + ' ul.tabNavigation a').removeClass('selected');
            $(this).addClass('selected');
            return false;
        }).filter(':first').click();
    }
    else {
        $('#' + id + ' ul.tabNavigation a').mouseover(function () {
            tabContainers.hide().filter(this.hash).show();
            $('#' + id + ' ul.tabNavigation a').removeClass('selected');
            $(this).addClass('selected');
            return false;
        }).filter(':first').mouseenter();
    }
}

$(document).ready(function () {
    $(window).scroll(function () {
        if ($(this).scrollTop() != 0) {
            $('#BackTop').fadeIn();
        } else {
            $('#BackTop').fadeOut();
        }
    });
    $('#BackTop').click(function () {  //back to top
        $('body,html').animate({scrollTop: 0}, 500);
    });
    $("#music_btn").click(function () {
        if ($(this).attr("flag") === "true") {
            $(this).attr("flag", false);
            $(this).css("background", "url(images/template/music_open.png)");
            document.getElementById("music").play();
        } else {
            $(this).attr("flag", true);
            $(this).css("background", "url(images/template/music_close.png)");
            document.getElementById("music").pause();

        }
    })
    $("#notice").hover(function () {
        $("#notice_content").show();
    }, function () {
        $("#notice_content").hide();
    })
    $(".delivery").click(function () {
        if (confirm("Are you sure the order already delivered?")) {
            send = {};
            send.oid = $(this).attr("data");
            send.action = "delivery";
            $.ajax({
                url: 'account_history.php',
                data: send,
                type: 'POST',
                dataType: 'json',
                success: function (data) {
                    if (data.status == 1) {
                        $("#order_status_" + data.data["orders_id"]).text(data.data["orders_status_name"]);
                        $(".delivery").remove();
                    } else {
                        location.reload();
                    }
                }
            });
        }
    });
});

var addTimer = function () {
    var list = [],
        interval;

    return function (id, time) {
        if (!interval)
            interval = setInterval(go, 1000);
        list.push({ele: document.getElementById(id), time: time});
    }

    function go() {
        for (var i = 0; i < list.length; i++) {
            list[i].ele.innerHTML = getTimerString(list[i].time ? list[i].time -= 1 : 0);
            if (!list[i].time)
                list.splice(i--, 1);
        }
    }

    function getTimerString(time) {
        var not0 = !!time,
            d = Math.floor(time / 86400),
            h = Math.floor((time %= 86400) / 3600),
            m = Math.floor((time %= 3600) / 60),
            s = time % 60;
        if (h < 10) h = '0' + h;
        if (m < 10) m = '0' + m;
        if (s < 10) s = '0' + s;

        if (time > 0) {
            return "<span>" + d + "</span> Days<span> " + h + "</span>:<span>" + m + "</span>:<span>" + s + "</span>";
        }
        else {
            return "Activity over";
        }
    }
}();

$(document).ready(function () {
    $(".address_title_right").toggle(function () {
        $(this).text('Show Address');
        $(".address_title_left").hide();
        $(".show_address").hide();
        $(".add_address").show();
    }, function () {
        $(this).text('Add Address');
        $(".address_title_left").show();
        $(".show_address").show();
        $(".add_address").hide();
    })

    $(".address_title_left").click(function () {
        $(".show_address table tr").show();
        $(".address_title_left").hide();
    })

    $('#add_addredd_btn').click(function () {
        var send = {};
        send.firstname = $("input[name='firstname']").val();
        send.lastname = $("input[name='lastname']").val();
        send.company = $("input[name='company']").val();
        send.street_address = $("input[name='street_address']").val();
        send.suburb = $("input[name='suburb']").val();
        send.postcode = $("input[name='postcode']").val();
        send.telephone = $("input[name='telephone']").val();
        send.city = $("input[name='city']").val();
        send.state = $("select[name='state']").val();
        send.country = $("select[name='country']").val();
        send.primary = 'on';
        send.formid = $("input[name='formid']").val();
        send.action = $("input[name='action']").val();
        send.type = 'ajax';
        console.log(send);
        $.post('/address_book_process.php', send, function (data) {
            if (data.status == 1) {
                alert(data.msg);
                location.reload();
            } else {
                alert(data.msg);
            }
        }, 'json');
    })
})

function getAddressStates(countryID, div_element) {
    var send = {};
    send.action = 'getStates';
    send.formid = $("input[name='formid']").val();
    send.country = countryID;
    $.ajax({
        type: "POST",
        url: "checkout/Ajax_buynow.php",
        data: send,
        timeout: 5000,
        beforeSend: function () {
            $("#indicator").show()
        },
        complete: function () {
            $('#indicator').hide()
        },
        error: function () {
            alert('select again')
        },
        success: function (msg) {
            $("#state").replaceWith(msg);
        }
    });
}

$(document).ready(function () {
    $(".claim_banner_product").click(function () {
        var bannersId = $(this).attr('data');
        $.getJSON("checkout/banner_product_customer.php?bannersId=" + bannersId, function (res) {
            if (res.status < 0) {
                location.href = res.redirect_url;
            } else {
                alert(res.msg);
            }
        })

    });
})