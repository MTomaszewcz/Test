import React, { Component } from "react";
import ArrRow from "./arrrow";

class Arr extends Component {
  state = {};
  render() {
    return (
      <div className="arr">
        <ArrRow />
        <ArrRow />
        <ArrRow />
      </div>
    );
  }
}

export default Arr;
