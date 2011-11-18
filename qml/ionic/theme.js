.pragma library

var progressColors = new Object
progressColors.day = "#0000FF"
progressColors.night = "#CCCCFF"
progressColors.sand = "#6C541E"

var backgrounds = new Object
backgrounds.day = "#F7F7F7"
backgrounds.night = "#000009"
backgrounds.sand = "#EDC9AF"

var webThemes = new Object
webThemes.day = "document.body.style.background = '#FFFFFB';document.body.style.color = '#000000';document.body.style.padding = '';document.body.style.margin = '';"
webThemes.night = "document.body.style.background = '#000009';document.body.style.color = '#FFFFFF';document.body.style.padding = '0px';document.body.style.margin = '0px';"
webThemes.sand = "document.body.style.background = '#EDC9AF';document.body.style.color = '#000000';document.body.style.padding = '';document.body.style.margin = '';"

function background(style) {
    return backgrounds[style]
}

function progressColor(style) {
    return progressColors[style]
}

function webTheme(style) {
    return webThemes[style]
}
