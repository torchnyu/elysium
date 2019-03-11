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
open Belt;

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

[@bs.val] external unsafeJsonParse: string => 'a = "JSON.parse";

let createSession = (self, session) => {
  self.ReasonReact.send(CreateSession(session));
  switch (Js.Json.stringifyAny(session)) {
  | Some(stringifiedSession) => Dom.Storage.(localStorage |> setItem("session", stringifiedSession))
  | None => ()
  };
};

let rehydrateSession = () => Option.map(Dom.Storage.(localStorage |> getItem("session")), unsafeJsonParse);

let make = _children => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => {
    currentPage: urlToPage(ReasonReact.Router.dangerouslyGetInitialUrl()),
    watcherID: ref(None),
    currentSession: rehydrateSession(),
  },
  reducer: (action, state) =>
    switch (action) {
    | GoTo(page) => ReasonReact.Update({...state, currentPage: page})
    | CreateSession(session) => ReasonReact.Update({...state, currentSession: Some(session)})
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
    <div className=Styles.app>
      <Header currentSession={self.state.currentSession} />
      {switch (self.state.currentPage) {
       | MainPage => <ProjectsList />
       | ProjectPage(slug) => <ProjectPage slug />
       | SubmitProjectPage => <SubmitProjectPage />
       | LoginPage => <LoginPage createSession={createSession(self)} />
       | NotFoundPage => <div> {ReasonReact.string("Page not found")} </div>
       }}
    </div>;
  },
};
