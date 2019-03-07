module Styles = {
  open Css;
  let projects = style([display(`flex), flexDirection(column)]);
};

let component = ReasonReact.statelessComponent("Projects");

module GetProjects = [%graphql {|
 query getProjects {
    projects {
      id
      name
    }
 }
|}];

module GetProjectsQuery = ReasonApollo.CreateQuery(GetProjects);

[@bs.deriving jsConverter]
type project = {
  id: int,
  name: string,
};

let make = (_children, ~projects) => {
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
                        slug="aletheia"
                        name={projectRecord.name}
                        color="EA526F"
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
