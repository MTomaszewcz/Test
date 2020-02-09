import React, { Component } from "react";
import Box from "./box";

class ArrRow extends Component {
  constructor(props) {
    super(props);
    this.state = {};
  }
  render() {
    return (
      <div className="row">
        <Box
          inc={this.props.inc}
          zdj="https://i.picsum.photos/id/237/305/120.jpg"
          tytul="czarny pies"
          tekst="miluśny"
        />
        <Box inc={this.props.inc} />
        <Box inc={this.props.inc} />
        <Box inc={this.props.inc} />
      </div>
    );
  }
}

export default ArrRow;
