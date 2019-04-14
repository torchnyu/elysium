let component = ReasonReact.statelessComponent("ProjectsGrid");

module Styles = {
  open Css;
  let projectsGrid =
    style([
      display(grid),
      gridGap(px(40)),
      width(vw(90.0)),
      justifyContent(center),
      gridAutoColumns(px(500)),
      gridTemplateColumns([`repeat((`autoFill, px(400)))]),
    ]);
};

open Types;

let make = (~projects, _children) => {
  ...component,
  render: _self =>
    <div className=Styles.projectsGrid>
      ...{
           projects |> Array.map(({id, title, slug}: project) => <Project key={string_of_int(id)} name=title slug />)
         }
    </div>,
};
