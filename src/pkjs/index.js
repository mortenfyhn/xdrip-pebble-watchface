// Minimal JavaScript for testing xDrip communication
// Clay is temporarily disabled to test if it's causing the issue

console.log('xDrip watchface JS ready - minimal mode for testing');

Pebble.addEventListener('ready', function() {
  console.log('PebbleKit JS ready - xDrip should be able to communicate');
});

// Log any messages from the watch for debugging
Pebble.addEventListener('appmessage', function(e) {
  console.log('Watch message: ' + JSON.stringify(e.payload));
});
