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
  let contributors = style([padding(px(20))]);
  let images = style([display(`flex), flexDirection(column)]);
  let image = style([maxWidth(px(500)), padding(px(10))]);
};
let component = ReasonReact.statelessComponent("ProjectPage");

open Types;

module GetProjectBySlug = [%graphql
  {|
 query getProjectBySlug($slug: String!, $eventSlug: String!) {
    projectBySlugAndEvent(slug: $slug, eventSlug: $eventSlug) {
      id
      slug
      title
      description
      contributors {
        id
        displayName
      }
      media {
        id
        url
      }
    }
 }
|}
];

module GetProjectBySlugQuery = ReasonApollo.CreateQuery(GetProjectBySlug);

[@react.component]
let make = (_children, ~slug, ~eventSlug) => {
  let slugQuery = GetProjectBySlug.make(~slug, ~eventSlug, ());
  <GetProjectBySlugQuery variables=slugQuery##variables>
    {({result}) =>
       switch (result) {
       | Loading => <div> {React.string("Loading")} </div>
       | Error(error) => <div> {React.string(error##message)} </div>
       | Data(response) =>
         let project = projectFromJs(response##projectBySlugAndEvent);
         let contributors = response##projectBySlugAndEvent##contributors |> Array.map(user => userFromJs(user));
         let media = response##projectBySlugAndEvent##media |> Array.map(media => mediumFromJs(media));
         <div className=Styles.project>
           <h1> {React.string(project.title)} </h1>
           <p>
             {switch (project.description) {
              | None => React.string("No description")
              | Some(desc) => React.string(desc)
              }}
           </p>
           <h2> {React.string("Contributors")} </h2>
           <div className=Styles.contributors>
             {contributors
              |> Array.map((c: user) => <div key={string_of_int(c.id)}> {React.string(c.displayName)} </div>)
              |> React.array}
           </div>
           <div className=Styles.images>
             {media |> Array.map((m: medium) => <img className=Styles.image src={m.url} />) |> React.array}
           </div>
         </div>;
       }}
  </GetProjectBySlugQuery>;
};
