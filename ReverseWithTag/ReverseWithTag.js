/**
 * Tokenize text into Array(String)
 */
function tokenize(text) {
	if (text == '') return [];

	var startIndex = text.indexOf('<');
	var endIndex = text.indexOf('>');

	if (startIndex < 0) return [text];
	else if (startIndex == 0 ) {
		return [text.slice(0, endIndex + 1)].concat(
			tokenize(text.slice(endIndex + 1, text.length))
		);
	}

	return [text.slice(0, startIndex)].concat(
		tokenize(text.slice(startIndex, text.length))
	);
}

// Utility functions
function isTag(token) { return token[0] == '<'; }
function isCloseTag(token) { return isTag(token) && token[1] == '/'; }
function tagName(token) {
	var inside = isCloseTag(token) ? token.slice(2, -1) : token.slice(1, -1);
	return inside.split(' ')[0];
}

/**
 * Reverse tokens with tag preserved
 */
function reverseTokens(tokens) {
	function findCloseTag(index, name) {
		// Didn'to check error case
		if (tokens[index].indexOf("</" + name) == 0) return index;
		return findCloseTag(index + 1, name);
	}

	if (tokens.length == 0) return [];
	if (isTag(tokens[0])) {
		var closeIndex = findCloseTag(1, tagName(tokens[0]));
		var insideElement = tokens.slice(1, closeIndex);
		var afterElement = tokens.slice(closeIndex + 1, tokens.length);

		return reverseTokens(afterElement).concat([tokens[0]]).
			concat(reverseTokens(insideElement)).concat([tokens[closeIndex]]);
	}

	return reverseTokens(tokens.slice(1)).concat([tokens[0].split('').reverse().join('')]);
}

/**
 * Reverse text with tag preserved
 */
function reverse(text) {
	return reverseTokens(tokenize(text)).join('');
}


// ----------------------------------------------------------------
// Test
// ----------------------------------------------------------------
var origin = "Hello <b attr='some'>Bold <i>Italic</i> words</b> World";
//
//var tokens = tokenize(origin);
//tokens.forEach(function(token) {
//	console.log('Token [' + token + '] is ' +
//		(isTag(token) ? (isCloseTag(token) ? 'Close' : 'Open') + ' Tag' : 'Word')
//	);
//	if (isTag(token)) console.log('Name: ', tagName(token));
//});
//
var reverseText = reverse(origin);
console.log(reverseText);

