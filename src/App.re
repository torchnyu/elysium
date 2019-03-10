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

open Types;
type routes =
  | MainPage
  | ProjectPage(string)
  | NotFoundPage
  | SubmitProjectPage
  | LoginPage;

type state = {
  currentPage: routes,
  currentSession: option(session),
  watcherID: ref(option(ReasonReact.Router.watcherID)),
};

type action =
  | GoTo(routes)
  | CreateSession(session);

let component = ReasonReact.reducerComponent("App");

let urlToPage = (url: ReasonReact.Router.url) =>
  switch (url.path) {
  | ["projects", slug] => ProjectPage(slug)
  | ["submit"] => SubmitProjectPage
  | ["login"] => LoginPage
  | [] => MainPage
  | _ => NotFoundPage
  };

let make = _children => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => {
    currentPage: urlToPage(ReasonReact.Router.dangerouslyGetInitialUrl()),
    watcherID: ref(None),
    currentUser: None,
  },
  reducer: (action, state) =>
    switch (action) {
    | GoTo(page) => ReasonReact.Update({...state, currentPage: page})
    },
  didMount: self => {
    let watcherID = ReasonReact.Router.watchUrl(url => self.send(GoTo(urlToPage(url))));
    self.state.watcherID := Some(watcherID);
    ();
  },
  willUnmount: self =>
    switch (self.state.watcherID^) {
    | Some(id) => ReasonReact.Router.unwatchUrl(id)
    | None => ()
    },
  render: self => {
    let createSession = session => self.send(CreateSession(session));
    <div className=Styles.app>
      <Header />
      {switch (self.state.currentPage) {
       | MainPage => <ProjectsList />
       | ProjectPage(slug) => <ProjectPage slug />
       | SubmitProjectPage => <SubmitProjectPage />
       | LoginPage => <LoginPage createSession />
       | NotFoundPage => <div> {ReasonReact.string("Page not found")} </div>
       }}
    </div>;
  },
};
