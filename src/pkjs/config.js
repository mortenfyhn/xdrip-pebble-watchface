module.exports = [
  {
    "type": "heading",
    "defaultValue": "xDrip Watchface Settings"
  },
  {
    "type": "text",
    "defaultValue": "Configure your blood glucose watchface."
  },
  {
    "type": "section",
    "items": [
      {
        "type": "heading",
        "defaultValue": "Graph Settings"
      },
      {
        "type": "slider",
        "messageKey": "GraphHours",
        "defaultValue": 3,
        "label": "Graph Hours",
        "description": "Number of hours to show in the graph",
        "min": 1,
        "max": 12,
        "step": 1
      }
    ]
  },
  {
    "type": "submit",
    "defaultValue": "Save Settings"
  }
];
