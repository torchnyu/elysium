module Styles = {
  open Css;
  let projects = style([display(`flex), flexDirection(column)]);
};

open Types;

let component = ReasonReact.statelessComponent("Projects");

module GetProjects = [%graphql
  {|
 query getProjects {
    projects {
      id
      title
      slug
      description
    }
 }
|}
];

module GetProjectsQuery = ReasonApollo.CreateQuery(GetProjects);

let make = _children => {
  ...component,
  render: _self => {
    <GetProjectsQuery>
      ...{({result}) =>
        switch (result) {
        | Loading => <div> {ReasonReact.string("Loading")} </div>
        | Error(error) => <div> {ReasonReact.string(error##message)} </div>
        | Data(response) =>
          <div>
            {<div className=Styles.projects>
               {ReasonReact.array(
                  Array.map(
                    project => {
                      let projectRecord = projectFromJs(project);
                      <Project
                        key={string_of_int(projectRecord.id)}
                        slug={projectRecord.slug}
                        name={projectRecord.title}
                      />;
                    },
                    response##projects,
                  ),
                )}
             </div>}
          </div>
        }
      }
    </GetProjectsQuery>;
  },
};
