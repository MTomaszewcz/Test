import React, { Component } from "react";

import Top from "./components/top";
import Counter from "./components/counter";
import Arr from "./components/arr";

class MyApp extends Component {
  render() {
    return (
      <div>
        <Top />
        <Arr />
      </div>
    );
  }
}
export default MyApp;
