module Styles = {
  open Css;
  let event =
    style([
      paddingTop(px(50)),
      display(`flex),
      flexDirection(column),
      alignItems(center),
      justifyContent(center),
      minWidth(vw(90.0)),
      color(hex("232c33")),
    ]);
  let icon = style([width(px(20)), padding(px(4))]);
  let header = style([display(`flex), width(vw(90.))]);
  let buttons =
    style([display(`flex), alignItems(center), justifyContent(flexEnd), flexWrap(wrap), width(vw(80.))]);
  let photo = style([maxWidth(px(200)), maxHeight(px(200))]);
  let details = style([display(`flex), flexDirection(column), paddingLeft(px(25)), minWidth(px(300))]);
  let projectsHeader = style([fontSize(rem(2.0))]);
};
let component = ReasonReact.statelessComponent("ProjectPage");

open Types;

module GetEventBySlug = [%graphql
  {|
 query getEventBySlug($slug: String!) {
    eventBySlug(slug: $slug) {
      id
      name
      startTime
      endTime
      slug
      description
      projects {
        id
        slug
        title
        description
      }
    }
 }
|}
];

open Utils;
module GetEventBySlugQuery = ReasonApollo.CreateQuery(GetEventBySlug);

let make = (_children, ~slug) => {
  ...component,
  render: _self => {
    let slugQuery = GetEventBySlug.make(~slug, ());
    <GetEventBySlugQuery variables=slugQuery##variables>
      ...{({result}) =>
        switch (result) {
        | Loading => <div> {ReasonReact.string("Loading")} </div>
        | Error(error) => <div> <h2> {ReasonReact.string(error##message)} </h2> </div>
        | Data(response) =>
          let event = response##eventBySlug;
          let projects = response##eventBySlug##projects |> Array.map(project => projectFromJs(project));
          <div className=Styles.event>
            <div className=Styles.header>
              <img className=Styles.photo src="/img/event_placeholder.png" />
              <div className=Styles.details>
                <h1> {ReasonReact.string(event##name)} </h1>
                <DateRange
                  startTime={Js.Json.decodeNumber(event##startTime)}
                  endTime={Js.Json.decodeNumber(event##endTime)}
                />
                <div> <Icon className=Styles.icon iconType=LocationPin /> </div>
              </div>
              <div className=Styles.buttons>
                <a href={"/" ++ slug ++ "/submit"}> <Button> {ReasonReact.string("SUBMIT")} </Button> </a>
                <a href={"/" ++ slug ++ "/submit"}>
                  <Button color=Secondary> {ReasonReact.string("VISIT SITE")} </Button>
                </a>
              </div>
            </div>
            <p>
              {switch (event##description) {
               | None => ReasonReact.string("No description")
               | Some(desc) => ReasonReact.string(desc)
               }}
            </p>
            <h2 className=Styles.projectsHeader> {ReasonReact.string("Projects")} </h2>
            <ProjectsGrid projects eventSlug=slug />
          </div>;
        }
      }
    </GetEventBySlugQuery>;
  },
};
