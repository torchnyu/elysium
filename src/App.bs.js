// Generated by BUCKLESCRIPT VERSION 4.0.18, PLEASE EDIT WITH CARE
'use strict';

var Css = require("bs-css/src/Css.js");
var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var Caml_option = require("bs-platform/lib/js/caml_option.js");
var ReasonReact = require("reason-react/src/ReasonReact.js");
var Header$ReactTemplate = require("./Header.bs.js");
var ProjectPage$ReactTemplate = require("./ProjectPage.bs.js");
var ProjectsList$ReactTemplate = require("./ProjectsList.bs.js");

var projectsGrid = Css.style(/* :: */[
      Css.display(Css.grid),
      /* [] */0
    ]);

var app = Css.style(/* :: */[
      Css.display(/* flex */-1010954439),
      /* :: */[
        Css.flexDirection(Css.column),
        /* :: */[
          Css.alignItems(Css.center),
          /* :: */[
            Css.fontFamily("mr-eaves-xl-modern, Helvetica, sans-serif"),
            /* [] */0
          ]
        ]
      ]
    ]);

var Styles = /* module */[
  /* projectsGrid */projectsGrid,
  /* app */app
];

var component = ReasonReact.reducerComponent("App");

function urlToPage(url) {
  var match = url[/* path */0];
  if (match) {
    if (match[0] === "projects") {
      var match$1 = match[1];
      if (match$1 && !match$1[1]) {
        return /* ProjectPage */[match$1[0]];
      } else {
        return /* NotFoundPage */1;
      }
    } else {
      return /* NotFoundPage */1;
    }
  } else {
    return /* MainPage */0;
  }
}

function make(_children) {
  return /* record */[
          /* debugName */component[/* debugName */0],
          /* reactClassInternal */component[/* reactClassInternal */1],
          /* handedOffState */component[/* handedOffState */2],
          /* willReceiveProps */component[/* willReceiveProps */3],
          /* didMount */(function (self) {
              var watcherID = ReasonReact.Router[/* watchUrl */1]((function (url) {
                      return Curry._1(self[/* send */3], /* GoTo */[urlToPage(url)]);
                    }));
              self[/* state */1][/* watcherID */1][0] = Caml_option.some(watcherID);
              return /* () */0;
            }),
          /* didUpdate */component[/* didUpdate */5],
          /* willUnmount */(function (self) {
              var match = self[/* state */1][/* watcherID */1][0];
              if (match !== undefined) {
                return ReasonReact.Router[/* unwatchUrl */2](Caml_option.valFromOption(match));
              } else {
                return /* () */0;
              }
            }),
          /* willUpdate */component[/* willUpdate */7],
          /* shouldUpdate */component[/* shouldUpdate */8],
          /* render */(function (self) {
              var match = self[/* state */1][/* currentPage */0];
              return React.createElement("div", {
                          className: app
                        }, ReasonReact.element(undefined, undefined, Header$ReactTemplate.make(/* array */[])), typeof match === "number" ? (
                            match !== 0 ? React.createElement("div", undefined, "Page not found") : ReasonReact.element(undefined, undefined, ProjectsList$ReactTemplate.make(/* array */[]))
                          ) : ReasonReact.element(undefined, undefined, ProjectPage$ReactTemplate.make(/* array */[], match[0])));
            }),
          /* initialState */(function (param) {
              return /* record */[
                      /* currentPage */urlToPage(ReasonReact.Router[/* dangerouslyGetInitialUrl */3](/* () */0)),
                      /* watcherID : record */[/* contents */undefined]
                    ];
            }),
          /* retainedProps */component[/* retainedProps */11],
          /* reducer */(function (action, state) {
              return /* Update */Block.__(0, [/* record */[
                          /* currentPage */action[0],
                          /* watcherID */state[/* watcherID */1]
                        ]]);
            }),
          /* jsElementWrapped */component[/* jsElementWrapped */13]
        ];
}

exports.Styles = Styles;
exports.component = component;
exports.urlToPage = urlToPage;
exports.make = make;
/* projectsGrid Not a pure module */
