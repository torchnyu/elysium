module Styles = {
  open Css;
  let icon = style([width(px(20)), padding(px(4))]);
  let date = style([display(`flex), alignItems(center)]);
};

open Utils;
let component = ReasonReact.statelessComponent("DateRange");

let make = (~startTime, ~endTime, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.date>
      <Icon className=Styles.icon iconType=Calendar />
      {ReasonReact.string(dateRangeToStr(startTime, endTime))}
    </div>,
};
