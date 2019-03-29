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
        name
        color
        slug
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
        | Error(error) => <div> {ReasonReact.string(error##message)} </div>
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
            <div>
              ...{
                   projects
                   |> Array.map(({id, name, color, slug}: project) =>
                        <Project key={string_of_int(id)} name slug color />
                      )
                 }
            </div>
          </div>;
        }
      }
    </GetEventBySlugQuery>;
  },
};
