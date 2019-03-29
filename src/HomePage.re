module Styles = {
  open Css;
  let hero =
    style([
      display(`flex),
      flexDirection(column),
      alignItems(center),
      justifyContent(center),
      color(white),
      width(vw(100.0)),
      background(linearGradient(`deg(0), [(0, hex("0267C1")), (100, Theme.darkBlue)])),
    ]);
  let searchBar =
    style([
      padding(px(15)),
      margin(px(20)),
      fontSize(rem(1.2)),
      borderRadius(px(25)),
      width(vw(50.)),
      borderColor(transparent),
      marginBottom(px(100)),
    ]);
  let heroText = style([fontWeight(`medium), margin(px(0))]);
  let heroSubtext = style([fontWeight(`light), margin(px(0)), fontSize(rem(1.3))]);
  let events = style([display(`flex), flexDirection(column), alignItems(center)]);
  let secondSection = style([transform(translateY(px(-50)))]);
};

let component = ReasonReact.statelessComponent("HomePage");

module GetEvents = [%graphql
  {|
 query getEvents {
    events {
      id
      slug
      name
      startTime
      endTime
      description
    }
 }
|}
];

module GetEventsQuery = ReasonApollo.CreateQuery(GetEvents);

let make = _children => {
  ...component,
  render: _self => {
    <div>
      <div className=Styles.hero>
        <h1 className=Styles.heroText> {ReasonReact.string("Find hackathons near you")} </h1>
        <h2 className=Styles.heroSubtext> {ReasonReact.string("Elysium is the central hub for hackathons")} </h2>
        <input className=Styles.searchBar type_="text" placeholder="Search for an event" />
      </div>
      <div className=Styles.secondSection>
        <GetEventsQuery>
          ...{({result}) =>
            switch (result) {
            | Loading => <div> {ReasonReact.string("Loading")} </div>
            | Error(error) => <div> {ReasonReact.string(error##message)} </div>
            | Data(response) =>
              <div>
                {<div className=Styles.events>
                   {ReasonReact.array(
                      Array.map(
                        event =>
                          <Event
                            key={string_of_int(event##id)}
                            name=event##name
                            startTime={Js.Json.decodeNumber(event##startTime)}
                            endTime={Js.Json.decodeNumber(event##endTime)}
                            slug={event##slug}
                          />,
                        response##events,
                      ),
                    )}
                 </div>}
              </div>
            }
          }
        </GetEventsQuery>
      </div>
    </div>;
  },
};
