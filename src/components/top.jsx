import React, { Component } from "react";

class Top extends Component {
  render() {
    return (
      <div id="navidiv">
        <nav id="navibar">
          <h1 className="navele" id="logo">
            Miso
          </h1>

          <ul className="navele">
            <li className="links">
              <a href="#">YouTube</a>
            </li>
            <li className="links">
              <a href="#">Twitter</a>
            </li>
            <li className="links">
              <a href="#">Facebook</a>
            </li>
          </ul>
        </nav>
      </div>
    );
  }
}

export default Top;
