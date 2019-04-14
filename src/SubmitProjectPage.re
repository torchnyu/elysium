open Types;

type actions =
  | ProjectCreated(project)
  | PreviousPage;

type page =
  | CreateProject
  | UploadImages;

type state = {
  page,
  project: option(project),
};

let component = ReasonReact.reducerComponent("SubmitProjectForm");

let make = (~session, ~createSession, ~eventSlug, _children) => {
  let finishSubmitProject = (self, session, project) => {
    createSession(session);
    self.ReasonReact.send(ProjectCreated(project));
  };
  {
    ...component,
    initialState: () => {page: UploadImages, project: None},
    reducer: (action, state) =>
      switch (action) {
      | ProjectCreated(project) => ReasonReact.Update({page: UploadImages, project: Some(project)})
      | PreviousPage => ReasonReact.Update({...state, page: CreateProject})
      },
    render: self => {
      <div>
        <h1> {ReasonReact.string("Submit A Project")} </h1>
        {switch (self.state.page, self.state.project) {
         | (CreateProject, _) =>
           <CreateProjectForm eventSlug session finishSubmitProject={finishSubmitProject(self)} />
         | (UploadImages, Some(project)) => <FileUploader resourceName="project" resourceId={project.id} />
         | (UploadImages, None) => <FileUploader resourceName="project" resourceId=5 />
         }}
      </div>;
    },
  };
};
