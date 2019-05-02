open Css;
let darkBlue = hex("0d186e");
let lightBlue = hex("0267C1");
let errorBackground = hex("ffc0c0");
let white = hex("ffffff");
let black = hex("000000");
let sansSerif = "source-sans-pro, sans-serif";
let buttonGradient = linearGradient(deg(90), [(0, hex("fd6940")), (100, hex("fecb7d"))]);

let primaryButtonStyles = [backgroundImage(buttonGradient), color(white)];
let secondaryButtonStyles = [borderColor(orange), color(orange), borderWidth(px(5))];
