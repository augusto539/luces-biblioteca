var music;
var elemet;

let buttoms = ['uncheck', 'uncheck', 'uncheck', 'uncheck', 'uncheck', 'uncheck', 'uncheck', 'uncheck', 'uncheck']

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
    }


}



/*



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

*/