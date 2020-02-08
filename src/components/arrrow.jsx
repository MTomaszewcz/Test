import React, { Component } from "react";
import Box from "./box";

class ArrRow extends Component {
  state = {};
  render() {
    return (
      <div className="row">
        <Box
          zdj="https://i.picsum.photos/id/237/305/120.jpg"
          tytul="czarny pies"
          tekst="miluśny"
        />
        <Box />
        <Box />
        <Box />
      </div>
    );
  }
}

export default ArrRow;
