module Styles = {
  open Css;
  let projectsGrid = style([display(grid)]);
  let app =
    style([
      display(`flex),
      flexDirection(column),
      alignItems(center),
      fontFamily("mr-eaves-xl-modern, Helvetica, sans-serif"),
    ]);
};

type routes =
  | MainPage
  | ProjectPage(string)
  | NotFoundPage;

type state = {
  currentPage: routes,
  watcherID: ref(option(ReasonReact.Router.watcherID)),
};

type action =
  | GoTo(routes);

let component = ReasonReact.reducerComponent("App");

open Types;

let projects = [
  (
    "aletheia",
    {name: "Aletheia", color: "0AD3FF", description: "The single source of truth for all HackNYU services"},
  ),
  (
    "saber",
    {name: "Saber", color: "FF8A5B", description: "A lean, row polymorphic gradually typed language for WebAssembly"},
  ),
  ("website", {name: "Website", color: "EA526F", description: "HackNYU's event website and registration system"}),
  ("org-site", {name: "Org Site", color: "C0DF85", description: "HackNYU's org site for info and recruiting"}),
  ("stuyspec", {name: "Stuyspec", color: "7DDF64", description: "Stuyvesant's newspaper that nobody reads"}),
  ("greedux", {name: "Greedux", color: "254E70", description: "A build system for React using Gulp"}),
];

let make = _children => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => {currentPage: MainPage, watcherID: ref(None)},
  reducer: (action, state) =>
    switch (action) {
    | GoTo(page) => ReasonReact.Update({...state, currentPage: page})
    },
  didMount: self => {
    let watcherID =
      ReasonReact.Router.watchUrl(url =>
        switch (url.path) {
        | ["projects", slug] => self.send(GoTo(ProjectPage(slug)))
        | [] => self.send(GoTo(MainPage))
        | _ => self.send(GoTo(NotFoundPage))
        }
      );
    self.state.watcherID := Some(watcherID);
    ();
  },
  willUnmount: self =>
    switch (self.state.watcherID^) {
    | Some(id) => ReasonReact.Router.unwatchUrl(id)
    | None => ()
    },
  render: self => {
    <div className=Styles.app>
      <Header />
      {switch (self.state.currentPage) {
       | MainPage => <ProjectsList projects />
       | ProjectPage(slug) => <ProjectPage project={List.assoc(slug, projects)} />
       | NotFoundPage => <div> {ReasonReact.string("Page not found")} </div>
       }}
    </div>;
  },
};
