module Styles = {
  open Css;
  let project =
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

module GetProjectBySlug = [%graphql
  {|
 query getProjectBySlug($slug: String!) {
    projectBySlug(slug: $slug) {
      id
      name
      slug
      color
      description
    }
 }
|}
];

module GetProjectBySlugQuery = ReasonApollo.CreateQuery(GetProjectBySlug);

let make = (_children, ~slug) => {
  ...component,
  render: _self => {
    let slugQuery = GetProjectBySlug.make(~slug, ());
    <GetProjectBySlugQuery variables=slugQuery##variables>
      ...{({result}) =>
        switch (result) {
        | Loading => <div> {ReasonReact.string("Loading")} </div>
        | Error(error) => <div> {ReasonReact.string(error##message)} </div>
        | Data(response) =>
          let project = projectFromJs(response##projectBySlug);
          <div className=Styles.project>
            <h1> {ReasonReact.string(project.name)} </h1>
            <p>
              {switch (project.description) {
               | None => ReasonReact.string("No description")
               | Some(desc) => ReasonReact.string(desc)
               }}
            </p>
          </div>;
        }
      }
    </GetProjectBySlugQuery>;
  },
};
