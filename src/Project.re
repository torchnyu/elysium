module Styles = {
  open Css;
  let project = projectColor =>
    style([
      display(`flex),
      flexDirection(column),
      alignItems(center),
      justifyContent(center),
      minHeight(px(300)),
      minWidth(px(400)),
      marginBottom(px(200)),
      backgroundColor(hex(projectColor)),
      `transition("box-shadow 0.2s"),
      hover([boxShadow(rgba(0, 0, 0, 0.75), ~x=px(7), ~y=px(7), ~blur=px(27), ~spread=px(-2))]),
      color(hex("FFFFFF")),
    ]);

  let name = style([textDecoration(none)]);
};

let component = ReasonReact.statelessComponent("Project");

let make = (_children, ~name, ~slug, ~color) => {
  ...component,
  render: _self => {
    <Link href={"/projects/" ++ slug} className={Styles.project(color)}>
      <h1 className=Styles.name> {ReasonReact.string(name)} </h1>
    </Link>;
  },
};
