open Types;

type actions =
  | ProjectCreated(project);

type page =
  | CreateProject
  | UploadImages;

type state = {
  page,
  project: option(project),
};

let component = ReasonReact.reducerComponent("SubmitProjectForm");

let handleFiles = (files: array(Js.t(string))) => {
  let file = Belt.Array.getExn(files, 0);
  let headers =
    Js.Dict.(
      {
        let dict = empty();
        dict->set("Content-type", "multipart/form-data");
        dict;
      }
    );
  let headers = Axios.Headers.fromDict(headers);
  Js.Promise.(
    Axios.postDatac(Utils.apiUrl ++ "/media", file, Axios.makeConfig(~headers, ()))
    |> then_(response => resolve(Js.log(response##data)))
    |> catch(err => resolve(Js.log(err)))
    |> ignore
  );
  ();
};

let make = (~session, ~createSession, ~eventSlug, _children) => {
  let finishSubmitProject = (self, session, project) => {
    createSession(session);
    self.ReasonReact.send(ProjectCreated(project));
  };
  {
    ...component,
    initialState: () => {page: CreateProject, project: None},
    reducer: (action, _state) =>
      switch (action) {
      | ProjectCreated(project) => ReasonReact.Update({page: UploadImages, project: Some(project)})
      },
    render: self => {
      <div>
        <h1> {ReasonReact.string("Submit A Project")} </h1>
        {switch (self.state.page) {
         | CreateProject => <CreateProjectForm eventSlug session finishSubmitProject={finishSubmitProject(self)} />
         | UploadImages => <FileUploader handleFiles />
         }}
      </div>;
    },
  };
};
