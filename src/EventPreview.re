module Styles = {
  open Css;
  let event =
    style([
      display(`flex),
      alignItems(center),
      width(px(500)),
      justifyContent(flexStart),
      textDecoration(none),
      backgroundColor(white),
      borderRadius(px(10)),
      margin(px(20)),
      boxShadow(rgba(0, 0, 0, 0.75), ~x=px(7), ~y=px(-1), ~blur=px(33), ~spread=px(-15)),
    ]);
  let name = style([color(hex(""))]);
  let location = style([display(`flex), alignItems(center)]);
  let icon = style([width(px(20)), padding(px(4))]);
  let date = style([display(`flex), alignItems(center)]);
  let image = style([width(px(200)), height(px(200)), unsafe("object-fit", "contain")]);
  let info = style([display(`flex), flexDirection(column)]);
};
open Utils;
let component = ReasonReact.statelessComponent("Event");

let make = (~name, ~startTime, ~endTime, ~slug, _children) => {
  ...component,
  render: _self => {
    <a href={"/" ++ slug} className=Styles.event>
      <img className=Styles.image src="/img/stock.jpg" />
      <div className=Styles.info>
        <h2 className=Styles.name> {ReasonReact.string(name)} </h2>
        <div className=Styles.location>
          <Icon className=Styles.icon iconType=LocationPin />
          {ReasonReact.string("Toronto, Canada")}
        </div>
        <div className=Styles.date>
          <Icon className=Styles.icon iconType=Calendar />
          {switch (startTime, endTime) {
           | (Some(startTime), Some(endTime)) =>
             ReasonReact.string(
               dateFloatToAbbr(startTime) ++ {js| – |js} ++ dateFloatToAbbr(endTime) ++ " " ++ getYear(endTime),
             )
           | (_, _) => ReasonReact.string("N/A")
           }}
        </div>
      </div>
    </a>;
  },
};
