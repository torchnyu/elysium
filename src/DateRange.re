module Styles = {
  open Css;
  let icon = style([width(px(20)), padding(px(4))]);
  let date = style([display(`flex), alignItems(center)]);
};

open Utils;

[@react.component]
let make = (~startTime, ~endTime, ~children=React.null) => {
  <div className=Styles.date> <div> children </div> {React.string(dateRangeToStr(startTime, endTime))} </div>;
};
