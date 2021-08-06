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
}