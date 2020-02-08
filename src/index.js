import React from "react";
import ReactDOM from "react-dom";
import "./index.css";
import MyApp from "./App";
import * as serviceWorker from "./serviceWorker";
import "bootstrap/dist/css/bootstrap.css";
//import Counter from "./components/top";

//ReactDOM.render(<Counter />, document.getElementById("root"));

ReactDOM.render(<MyApp />, document.getElementById("root"));

serviceWorker.unregister();
