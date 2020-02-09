import React, { Component } from "react";

class Counter extends Component {
  constructor(props) {
    super(props);
    this.state = {
      count: 0,
      tags: ["tag1", "tag2", "tag3"]
    };
  }

  render() {
    return (
      <div style={{ background: "#425b6c" }}>
        <span
          style={{ fontSize: 20, width: "60px" }}
          className={this.getBadgeClasses()}
        >
          {this.formatCount()}
        </span>
        <button
          type="button"
          className="btn btn-primary"
          onClick={this.props.inc}
        >
          increment
        </button>

        {this.decButton()}

        <ul>
          {this.state.tags.map((tag) => (
            <li key={tag}>{tag}</li>
          ))}
        </ul>
      </div>
    );
  }

  getBadgeClasses() {
    let classes = "badge m-2 badge-";
    classes += this.props.cnt === 0 ? "warning" : "primary";
    return classes;
  }

  formatCount() {
    //const { count } = this.state;
    const a = this.props.cnt;
    return a === 0 ? "Zero" : a;
  }

  decButton() {
    let decStyle = {
      display: this.props.cnt === 0 && "none"
    };

    return (
      <buton
        type="button"
        className="btn btn-warning"
        style={decStyle}
        onClick={this.props.dec}
      >
        decrement
      </buton>
    );
  }
}

export default Counter;
