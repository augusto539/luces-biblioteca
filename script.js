var music;
var elemet;

function playMusic(){
    music = new Audio('sound-14.mp3');
    music.play();
}

function togle(id){
    elemet = document.getElementById(id).className;

    if (elemet == 'uncheck'){
        document.getElementById(id).className = "check";
    }
    else
    {
        document.getElementById(id).className = "uncheck";
    }

    if (id == 6 && elemet == 'uncheck'){
        document.getElementById(0).className = "check";
        document.getElementById(1).className = "check";
        document.getElementById(2).className = "check";
        document.getElementById(3).className = "check";
        document.getElementById(4).className = "check";
        document.getElementById(5).className = "check";

        document.getElementById(7).className = "uncheck"; 
        document.getElementById(8).className = "uncheck"; 
    } if (id == 6 && elemet == 'check'){
        document.getElementById(0).className = "uncheck";
        document.getElementById(1).className = "uncheck";
        document.getElementById(2).className = "uncheck";
        document.getElementById(3).className = "uncheck";
        document.getElementById(4).className = "uncheck";
        document.getElementById(5).className = "uncheck"; 
    }


    if (id == 7 && elemet == 'uncheck'){
        document.getElementById(0).className = "check";
        document.getElementById(1).className = "check";
        document.getElementById(2).className = "check";
        document.getElementById(3).className = "check";

        document.getElementById(4).className = "uncheck";
        document.getElementById(5).className = "uncheck";
        document.getElementById(6).className = "uncheck"; 
        document.getElementById(8).className = "uncheck"; 
    } if (id == 7 && elemet == 'check'){
        document.getElementById(0).className = "uncheck";
        document.getElementById(1).className = "uncheck";
        document.getElementById(2).className = "uncheck";
        document.getElementById(3).className = "uncheck";
    }

    if (id == 8 && elemet == 'uncheck'){
        document.getElementById(4).className = "check";
        document.getElementById(5).className = "check";

        document.getElementById(0).className = "uncheck";
        document.getElementById(1).className = "uncheck";
        document.getElementById(2).className = "uncheck"; 
        document.getElementById(3).className = "uncheck"; 

        document.getElementById(6).className = "uncheck"; 
        document.getElementById(7).className = "uncheck"; 
    } if (id == 8 && elemet == 'check'){
        document.getElementById(4).className = "uncheck";
        document.getElementById(5).className = "uncheck";
    }
}