let music;
let elemet;
let strLED1 = "";
let strLED2 = "";
let LED2_state = 0;

let buttoms = ['uncheck', 'uncheck', 'uncheck', 'uncheck', 'uncheck', 'uncheck', 'uncheck', 'uncheck', 'uncheck']

function GetArduinoIO()
{
    nocache = "&nocache=" + Math.random() * 1000000;
    var request = new XMLHttpRequest();
            
    // send HTTP GET request with LEDs to switch on/off if any
    request.open("GET", "ajax_inputs" + strRELAY1 + strRELAY2 + strRELAY3 + strRELAY4 + strRELAY5 + strRELAY6 + nocache, true);
    request.send(null);
    setTimeout('GetArduinoIO()', 1000);
    strRELAY1 , strRELAY2, strRELAY3, strRELAY4, strRELAY5, strRELAY6 = "";
}


function playMusic(){
    music = new Audio('sound-14.mp3');
    music.play();
}

function togle(id){
    elemet = document.getElementById(id).className;

    if (elemet == 'uncheck'){
        if (id < 6) {
            buttoms[id] = 'check'
        }
        if (id == 6){
            for (let index = 0; index < buttoms.length; index++) {
                if (index < 7) {
                    buttoms[index] = 'check'
                } else {
                    buttoms[index] = 'uncheck'
                }
            }
        }
        if (id == 7) {
            for (let index = 0; index < buttoms.length; index++) {
                if (index < 4 || index == 7) {
                    buttoms[index] = 'check'
                } else {
                    buttoms[index] = 'uncheck'
                }
            }
        }
        if (id == 8) {
            for (let index = 0; index < buttoms.length; index++) {
                if (index == 4 || index == 5 || index == 8) {
                    buttoms[index] = 'check'
                } else {
                    buttoms[index] = 'uncheck'
                }
            }
        }
        
    } else {
        if (id < 6) {
            buttoms[id] = 'uncheck'
        }  
        if (id == 6) {
            for (let index = 0; index < buttoms.length; index++) {
                buttoms[index] = 'uncheck'  
            }
        }
        if (id == 7) {
            for (let index = 0; index < buttoms.length; index++) {
                if (index < 4 || index == 7) {
                    buttoms[index] = 'uncheck'
                } 
            }
        }
        if (id == 8) {
            for (let index = 0; index < buttoms.length; index++) {
                if (index == 4 || index == 5 || index == 8) {
                    buttoms[index] = 'uncheck'
                } 
            }
        }
    }

    if (buttoms[0] == 'check' && buttoms[1] == 'check' && buttoms[2] == 'check' && buttoms[3] == 'check' && buttoms[4] == 'check' && buttoms[5] == 'check') {
        buttoms[6] = 'check'
 
    } else {
        buttoms[6] = 'uncheck'
    }

    if (buttoms[0] == 'check' && buttoms[1] == 'check' && buttoms[2] == 'check' && buttoms[3] == 'check' && buttoms[4] != 'check' && buttoms[5] != 'check') {
        buttoms[7] = 'check'
    } else {
        buttoms[7] = 'uncheck'
    }

    if (buttoms[0] != 'check' && buttoms[1] != 'check' && buttoms[2] != 'check' && buttoms[3] != 'check' && buttoms[4] == 'check' && buttoms[5] == 'check') {
        buttoms[8] = 'check'
    } else {
        buttoms[8] = 'uncheck'
    }
    


    for (let index = 0; index < buttoms.length; index++) {
        document.getElementById(index).className = buttoms[index];   

        if (buttoms[index] == "check") {
            strRELAY[i+1] = `&Relay${i+1}=1`;
        }
        else {
            strRELAY[i+1] = `&Relay${i+1}=0`;
        }
    }


}
