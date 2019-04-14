[@bs.deriving jsConverter]
type project = {
  id: int,
  title: string,
  slug: string,
  description: option(string),
};

[@bs.deriving jsConverter]
type user = {
  id: int,
  displayName: string,
};

[@bs.deriving jsConverter]
type session = {
  token: string,
  user,
};

[@bs.deriving jsConverter]
type medium = {
  id: int,
  url: string,
};
