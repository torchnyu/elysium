[@bs.deriving jsConverter]
type project = {
  id: int,
  name: string,
  color: string,
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
