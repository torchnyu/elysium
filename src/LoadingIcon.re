module Styles = {
  open Css;
  let loadingIcon =
    style([
      display(`flex),
      alignItems(center),
      justifyContent(center),
      padding4(~top=px(20), ~bottom=px(20), ~left=px(100), ~right=px(100)),
      maxWidth(px(400)),
      backgroundColor(white),
      borderRadius(px(25)),
      boxShadow(rgba(0, 0, 0, 0.75), ~x=px(7), ~y=px(-1), ~blur=px(33), ~spread=px(-15)),
    ]);
};

[@react.component];
let make = () => {
  <div className=Styles.loadingIcon> <h1> {React.string("Loading")} </h1> </div>;
};
