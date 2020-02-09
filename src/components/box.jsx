import React, { Component } from "react";

class Box extends Component {
  constructor(props) {
    super(props);
    this.state = {};
  }
  render() {
    return (
      <div className="box">
        <div className="incell">
          <img
            onClick={this.props.inc}
            src="https://i.picsum.photos/id/227/305/120.jpg"
            alt="xxx"
          ></img>
          <h4>{this.props.tytul}</h4>
          <p>{this.props.tekst}</p>
        </div>
      </div>
    );
  }
}

export default Box;
