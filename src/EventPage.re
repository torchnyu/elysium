module Styles = {
  open Css;
  let event =
    style([
      display(`flex),
      flexDirection(column),
      alignItems(center),
      justifyContent(center),
      minWidth(vw(90.0)),
      color(hex("232c33")),
    ]);
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
            <h1> {ReasonReact.string(event##name)} </h1>
            <p>
              {switch (event##description) {
               | None => ReasonReact.string("No description")
               | Some(desc) => ReasonReact.string(desc)
               }}
            </p>
            <h2> {ReasonReact.string("Projects")} </h2>
            <a href={"/" ++ slug ++ "/submit"}> <Button> {ReasonReact.string("Submit a project")} </Button> </a>
            <div>
              ...{
                   projects
                   |> Array.map(({id, title, slug}: project) => <Project key={string_of_int(id)} name=title slug />)
                 }
            </div>
          </div>;
        }
      }
    </GetEventBySlugQuery>;
  },
};
