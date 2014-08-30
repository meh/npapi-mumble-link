Mumble Link
===========
This NPAPI plugin allows access to the Mumble Link data.

Live Object
-----------
The main entry point to the Mumle Link API, every time you access a property or
sub-object properties the value will be up to date.

### `version`

  The Mumble Link version.

### `tick`

The unique ID for the current Mumble Link data, it's updated by the game after
every frame.

### `name`

The name of the Mumble Link provider, usually the name of the game.

### `description`

Additional information about the Mumble Link provider.

### `context`

A `Context` object uniquely representing the context the player is in, for
example world, map, team and whatnot.

### `identity`

An uniquely identifying string for the character, usually a JSON string with
more information about the character.

### `avatar`

A `Space` object describing where the player is.

### `camera`

A `Space` object describing where the camera is.

### `snapshot()`

This method will return a `Snapshot` object.

Snapshot Object
---------------
The `Snapshot` object has all attributes of the `Live` object, but the values
are frozen to the moment the call was made.

Context Object
--------------
The `Context` object is an array-like object containing the bytes composing the
context identifier.

Space Object
------------
The `Space` object describes the position of an element in 3D space.

### `position`

A `Vector` describing the position of the element in 3D space.

### `front`

A `Vector` describing the orientation of the element in 3D space.

### `top`

A `Vector` describing where the character is looking at in 3D space.

Vector Object
-------------
Represent a point in 3D space.

### `x`

A double going towards *right*.

### `y`

A double going towards *up*.

### `z`

A double going towards the *front*.

Example
=======
To get access to the API you have to add an `<embed>` tag for the plugin to
work.

```html
<embed id="mumble" width="0" height="0" type="application/x-mumble-link">
```

In case it's not working, try adding the following code as early as possible.

```javascript
navigator.plugins.refresh(true);
```

Then you can access the `Live` properties and methods on the `<embed>` tag itself.

```javascript
function mumble() {
  return document.getElementById("mumble");
}

console.log(mumble().identity);
```

I advice to take snapshots instead of accessing the `Live` itself so as to keep
consistency between accesses in the same context.

For example if you're running some kind of DOM update in a setInterval:

```javascript
setInterval(function() {
  var m = mumble().snapshot();

  console.log(m.identity);
  console.log([m.avatar.position.x, m.avatar.position.y, m.avatar.position.z]);
}, 1000);
```
