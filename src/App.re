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
  | CreateSession(session)
  | DeleteSession;

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

let deleteSession = (self, ()) => {
  self.ReasonReact.send(DeleteSession);
  Dom.Storage.(localStorage |> removeItem("session"));
};

/* Functors are cool. Option.map takes in an optional value, a and a function f, a -> b
   then returns either Some(f(a)) if a is a value or None if a is None
   */
let rehydrateSession = () => Option.map(Dom.Storage.(localStorage |> getItem("session")), unsafeJsonParse);

let make = _children => {
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
    | DeleteSession => ReasonReact.Update({...state, currentSession: None})
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
      <Header deleteSession={deleteSession(self)} currentSession={self.state.currentSession} />
      {switch (self.state.currentPage, self.state.currentSession) {
       | (MainPage, _) => <ProjectsList />
       | (ProjectPage(slug), _) => <ProjectPage slug />
       | (SubmitProjectPage, Some(session)) =>
         <SubmitProjectPage createSession={createSession(self)} session={Some(session)} />
       | (SubmitProjectPage, None) =>
         ReasonReact.Router.push("/login");
         <LoginPage createSession={createSession(self)} />;
       | (LoginPage, None) => <LoginPage createSession={createSession(self)} />
       | (LoginPage, Some(_session)) =>
         ReasonReact.Router.push("/");
         <ProjectsList />;
       | (NotFoundPage, _) => <div> {ReasonReact.string("Page not found")} </div>
       }}
    </div>;
  },
};
