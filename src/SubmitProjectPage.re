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

[@react.component]
let make = (~session, ~createSession, ~eventSlug, _children) => {
  let (state, dispatch) =
    React.useReducer(
      (state, action) =>
        switch (action) {
        | ProjectCreated(project) => {page: UploadImages, project: Some(project)}
        | PreviousPage => {...state, page: CreateProject}
        },
      {page: UploadImages, project: None},
    );
  let finishSubmitProject = (session, project) => {
    createSession(session);
    dispatch(ProjectCreated(project));
  };
  <div>
    <h1> {React.string("Submit A Project")} </h1>
    {switch (state.page, state.project) {
     | (CreateProject, _) => <CreateProjectForm eventSlug session finishSubmitProject />
     | (UploadImages, Some(project)) =>
       <FileUploader className="" apiUrl=Constants.apiUrl resourceName="project" resourceId={project.id} />
     | (UploadImages, None) =>
       <FileUploader className="" apiUrl=Constants.apiUrl resourceName="project" resourceId=5 />
     }}
  </div>;
};
