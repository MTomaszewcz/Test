import React, { Component } from "react";
import ArrRow from "./arrrow";
import Counter from "./counter";

class Arr extends Component {
  constructor(props) {
    super(props);
    this.state = {
      count: 0
    };
    this.increment = this.increment.bind(this);
    this.decrement = this.decrement.bind(this);
  }
  render() {
    return (
      <div>
        <Counter
          cnt={this.state.count}
          inc={this.increment}
          dec={this.decrement}
        />
        <div className="arr">
          <ArrRow inc={this.increment} />
          <ArrRow inc={this.increment} />
          <ArrRow inc={this.increment} />
        </div>
      </div>
    );
  }

  increment() {
    this.setState((prv) => {
      return {
        count: prv.count + 1
      };
    });
  }
  decrement() {
    this.setState((prv) => {
      return {
        count: prv.count === 0 ? 0 : prv.count - 1
      };
    });
  }
}

export default Arr;
