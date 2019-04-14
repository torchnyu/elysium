module Styles = {
  open Css;
  let project =
    style([
      display(`flex),
      flexDirection(column),
      alignItems(center),
      justifyContent(center),
      minHeight(px(300)),
      width(px(300)),
      marginBottom(px(200)),
      `transition("box-shadow 0.2s"),
      boxShadow(rgba(0, 0, 0, 0.75), ~x=px(7), ~y=px(7), ~blur=px(27), ~spread=px(-2)),
      color(hex("121212")),
    ]);

  let name = style([textDecoration(none)]);
};

let component = ReasonReact.statelessComponent("Project");

let make = (_children, ~name, ~eventSlug, ~slug) => {
  ...component,
  render: _self => {
    <Link href={"/" ++ eventSlug ++ "/" ++ slug} className=Styles.project>
      <Icon iconType=ProjectPlaceholder />
      <h1 className=Styles.name> {ReasonReact.string(name)} </h1>
    </Link>;
  },
};
