module Styles = {
  open Css;
  let header = isHome => {
    let headerShadow =
      if (isHome) {
        boxShadow(transparent);
      } else {
        boxShadow(~x=px(2), ~y=px(3), ~spread=px(-3), ~blur=px(10), rgba(0, 0, 0, 0.75));
      };
    style([
      display(`flex),
      flexDirection(row),
      alignItems(center),
      justifyContent(center),
      backgroundColor(if (isHome) {Theme.darkBlue} else {Theme.white}),
      color(if (isHome) {white} else {Theme.black}),
      headerShadow,
      width(vw(100.)),
      padding4(~top=px(2), ~left=px(0), ~right=px(0), ~bottom=px(2)),
      fontFamily(Theme.sansSerif),
    ]);
  };
  let masthead = isHome =>
    style([
      display(`flex),
      alignItems(center),
      height(`percent(100.)),
      fontWeight(bold),
      textDecoration(none),
      paddingLeft(px(40)),
      color(if (isHome) {Theme.white} else {Theme.black}),
    ]);
  let links = style([display(`flex), justifyContent(flexEnd), width(vw(80.0)), fontSize(rem(0.8))]);
  let link = isHome =>
    style([paddingLeft(px(20)), color(if (isHome) {Theme.white} else {Theme.black}), textDecoration(none)]);
};

[@react.component]
let make = (~currentSession, ~deleteSession, ~isHome) => {
  let links =
    switch (currentSession) {
    | Some(_session) => [|
        <a className={Styles.link(isHome)} href="#" onClick={_ => deleteSession()}>
          <h2> {React.string("SIGN OUT")} </h2>
        </a>,
      |]
    | None => [|
        <Link className={Styles.link(isHome)} href="/organizers"> <h2> {React.string("ORGANIZERS")} </h2> </Link>,
        <Link className={Styles.link(isHome)} href="/login"> <h2> {React.string("LOGIN")} </h2> </Link>,
        <Link className={Styles.link(isHome)} href="/register"> <h2> {React.string("SIGN UP")} </h2> </Link>,
      |]
    };
  <div className={Styles.header(isHome)}>
    <Link href="/" className={Styles.masthead(isHome)}> <h1> {React.string("elysium")} </h1> </Link>
    <div className=Styles.links> {React.array(links)} </div>
  </div>;
};
