$(function() {
    window.onload=function() {
        var x = document.getElementById("demo123");
        x.onclick=function() {
            $.ajax({
                dataType: 'json',
                url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
                type: 'POST',
                contentType: 'application/json',
                data: JSON.stringify({'Demo_App_Inputs_Wr': {'demomodeEnabled': 1}})
            })
            .done(function() {
                console.log('demo mode write success.');
            })
            .fail(function() {
                showSimplePopup('Error', 'Could not set value.');
                console.log('demo mode write fail.');
            })
            .always(function() {
            });
        }
        var el=document.getElementById('dig123');
        el.onclick=function() {
            var weight=prompt('Enter some weight');         
            $.ajax({
                dataType: 'json',
                url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
                type: 'POST',
                contentType: 'application/json',
                data: JSON.stringify({'Demo_App_Inputs_Wr': {'dig': 1, 'weight1': weight}})
            })
            .done(function() {
                console.log('dig success.');
            })
            .fail(function() {
                showSimplePopup('Error', 'Could not set value.');
                console.log('dig fail.');
            })
            .always(function() {
            });
        }
        var el1=document.getElementById('wrw123');
        el1.onclick=function() {
            $.ajax({
                dataType: 'json',
                url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
                type: 'POST',
                contentType: 'application/json',
                data: JSON.stringify({'Demo_App_Inputs_Wr': {'wrw': 1}})
            })
            .done(function() {
                console.log('wrw success.');
            })
            .fail(function() {
                showSimplePopup('Error', 'Could not set value.');
                console.log('wrw fail.');
            })
            .always(function() {
            });
        }
        var el2=document.getElementById('llw123');
        el2.onclick=function() {
            $.ajax({
                dataType: 'json',
                url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
                type: 'POST',
                contentType: 'application/json',
                data: JSON.stringify({'Demo_App_Inputs_Wr': {'llw': 1}})
            })
            .done(function() {
                console.log('llw success.');
            })
            .fail(function() {
                showSimplePopup('Error', 'Could not set value.');
                console.log('llw fail.');
            })
            .always(function() {
            });
        }
        var el3=document.getElementById('dump123');
        el3.onclick=function() {
            $.ajax({
                dataType: 'json',
                url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
                type: 'POST',
                contentType: 'application/json',
                data: JSON.stringify({'Demo_App_Inputs_Wr': {'dump': 1}})
            })
            .done(function() {
                console.log('dump success.');
            })
            .fail(function() {
                showSimplePopup('Error', 'Could not set value.');
                console.log('dump fail.');
            })
            .always(function() {
            });
        }
        var el4=document.getElementById('partial123');
        el4.onclick=function() {
            var my_delay=0;
            var remain=prompt("Enter weight that you want to remain");
            setTimeout(function() {
                $.ajax({
                    dataType: 'json',
                    url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
                    type: 'POST',
                    contentType: 'application/json',
                    data: JSON.stringify({'Demo_App_Inputs_Wr': {'pdump': 1, 'weight1': remain}})
                })
                .done(function() {
                    console.log('rack success.');
                })
                .fail(function() {
                    showSimplePopup('Error', 'Could not set value.');
                    console.log('rack fail.');
                })
                .always(function() {
                });
            }, my_delay++ * 6000);
            setTimeout(function() { 
                $.ajax({
                    dataType: 'json',
                    url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
                    type: 'POST',
                    contentType: 'application/json',
                    data: JSON.stringify({'Demo_App_Inputs_Wr': {'tiltposition': 100, 'tiltposition_rate': 35}})
                })
                .done(function() {
                    console.log('rack success.');
                })
                .fail(function() {
                    showSimplePopup('Error', 'Could not set value.');
                    console.log('rack fail.');
                })
                .always(function() {
                });
            }, my_delay++ * 1000);
        }
        var el6=document.getElementById('carry123');
        el6.onclick=function() {
            $.ajax({
                dataType: 'json',
                url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
                type: 'POST',
                contentType: 'application/json',
                data: JSON.stringify({'Demo_App_Inputs_Wr': {'carry': 1}})
            })
            .done(function() {
                console.log('carry success.');
            })
            .fail(function() {
                showSimplePopup('Error', 'Could not set value.');
                console.log('carry fail.');
            })
            .always(function() {
            });
        }
    }

    $('#store123').click(function() {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'StoreReqstEnable':1})
        })
        .done(function() {
            console.log('store success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not send store request.');
            console.error('store fail.');
        })
        .always(function() {
        });
    });

    $('#desired-lift-position-form').submit(function(ev) {  
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'Demo_App_Inputs_Wr': {'liftposition': Number($('#desired-lift-position-input').val())}})
        })
        .done(function() {
            $('#desired-lift-position-input').val('').change();
            $('#desired-lift-position-value').text('?');
            console.log('set liftposition success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not set value.');
            console.log('set desired-lift-position fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });
    $('#desired-lift-position-rate-form').submit(function(ev) {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'Demo_App_Inputs_Wr': {'liftposition_rate': Number($('#desired-lift-position-rate-input').val())}})
        })
        .done(function() {
            $('#desired-lift-position-rate-input').val('').change();
            $('#desired-lift-position-rate-value').text('?');
            console.log('set desired-lift-position-rate success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not set value.');
            console.log('set desired-lift-position-rate fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });
    $('#desired-tilt-position-form').submit(function(ev) {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'Demo_App_Inputs_Wr': {'tiltposition': Number($('#desired-tilt-position-input').val())}})
        })
        .done(function() {
            $('#desired-tilt-position-input').val('').change();
            $('#desired-tilt-position-value').text('?');
            console.log('set desired-tilt-position success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not set value.');
            console.log('set desired-tilt-position fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });
    $('#desired-tilt-position-rate-form').submit(function(ev) {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'Demo_App_Inputs_Wr': {'tiltposition_rate': Number($('#desired-tilt-position-rate-input').val())}})
        })
        .done(function() {
            $('#desired-tilt-position-rate-input').val('').change();
            $('#desired-tilt-position-rate-value').text('?');
            console.log('set desired-tilt-position-rate success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not set value.');
            console.log('set desired-tilt-position-rate fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });
    $('#payload-form').submit(function(ev) {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'Demo_App_Inputs_Wr': {'payload': Number($('#payload-input').val())}})
        })
        .done(function() {
            $('#payload-input').val('').change();
            $('#payload-value').text('?');
            console.log('set payload success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not set value.');
            console.log('set payload fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });
    $('#payload-rate-form').submit(function(ev) {
        $.ajax({
            dataType: 'json',
            url: '/CPM/cgi-bin/jhm2CgiApp.cgi?requestType=CommandRequest2',
            type: 'POST',
            contentType: 'application/json',
            data: JSON.stringify({'Demo_App_Inputs_Wr': {'payload_rate': Number($('#payload-rate-input').val())}})
        })
        .done(function() {
            $('#payload-rate-input').val('').change();
            $('#payload-rate-value').text('?');
            console.log('set payload-rate success.');
        })
        .fail(function() {
            showSimplePopup('Error', 'Could not set value.');
            console.log('set payload-rate fail.');
        })
        .always(function() {
        });
        ev.preventDefault();
    });
});

function showPopup(btn, header, body) {
    btn.button('loading');
    $('#pop-up-header').html(header);
    $('#pop-up-body').html(body);
    $('#pop-up').modal('show');
    $('#pop-up').one('hidden.bs.modal', function() {
        btn.button('reset');
    });
};

function showSimplePopup(header, body) {
    $('#pop-up-header').html(header);
    $('#pop-up-body').html(body);
    $('#pop-up').modal('show');
};

var otherEnabled = false;
function updateOther() {
    var x1 = $('#id1123'),
        y1 = $('#id2123'),
        z1 = $('#id3123');
    var t1 = " 100 250";
    var t2 = 0;
    var t3 = 0;
    const previous_lift1 = document.getElementById('id2123');
    var previous_lift = previous_lift1.getAttribute('to');
    const previous_tilt1 = document.getElementById('id1123');
    var previous_tilt = previous_tilt1.getAttribute('to');
    $.ajax({
        dataType: 'json',
        url: '/CPM/cgi-bin/jhm2CgiApp.cgi',
        data: { 'requestType': 'ParameterRequest2', 'paramsRequested': 'Demo_App_Inputs_Rd' },
        timeout: 1000
    })
    .done(function(data) {
        $('#desired-lift-position-value').text(Number(data.Demo_App_Inputs_Rd.Lift_Position.value).toFixed(2));
        $('#desired-lift-position-rate-value').text(Number(data.Demo_App_Inputs_Rd.Lift_Position_Rate.value).toFixed(2));
        $('#desired-tilt-position-value').text(Number(data.Demo_App_Inputs_Rd.Tilt_Position.value).toFixed(2));
        $('#desired-tilt-position-rate-value').text(Number(data.Demo_App_Inputs_Rd.Tilt_Position_Rate.value).toFixed(2));
        $('#payload-value').text(Number(data.Demo_App_Inputs_Rd.Payload.value).toFixed(2));
        $('#payload-rate-value').text(Number(data.Demo_App_Inputs_Rd.Payload_rate.value).toFixed(2));
        t2 = Number(data.Demo_App_Inputs_Rd.Lift_Angle.value).toFixed(1) * -1;
        t2 = t2 + t1;
        t3 = (Number(data.Demo_App_Inputs_Rd.Tilt_Angle.value).toFixed(2) - Number(data.Demo_App_Inputs_Rd.Lift_Angle.value).toFixed(2)) * -1;
        document.getElementById("id1123").setAttribute("from", previous_tilt);
        document.getElementById("id2123").setAttribute("from", previous_lift);
        document.getElementById("id3123").setAttribute("from", previous_lift);
        document.getElementById("id1123").setAttribute("to", t3);
        document.getElementById("id2123").setAttribute("to", t2);
        document.getElementById("id3123").setAttribute("to", t2);
        previous_tilt = previous_tilt1.getAttribute('to');
        previous_lift = previous_lift1.getAttribute('to');
        y1[0].beginElement();
        z1[0].beginElement();
        x1[0].beginElement();
        console.log("Lift Angle is", t2);
        console.log("Tilt Angle is", t3);
    })
    .fail(function() {
        $('#desired-lift-position-value').text('?');
        $('#desired-lift-position-rate-value').text('?');
        $('#desired-tilt-position-value').text('?');
        $('#desired-tilt-position-rate-value').text('?');
        $('#payload-value').text('?');
        $('#payload-rate-value').text('?');
    })
    .always(function() {
        if(otherEnabled) {
            setTimeout(updateOther, 3000);
        }
    });
};

$('#panel-2 .collapse').on('show.bs.collapse', function() {
    otherEnabled = true;
    updateOther();
});

$('#panel-2 .collapse').on('hide.bs.collapse', function() {
    otherEnabled = true;
    updateOther();
});
