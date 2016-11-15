'use strict';

const tagRE = /(<\/?[a-zA-Z]\w*\b[^>]*>)/

/**
 * Find tags & Slice into segments
 */
function tagSlice(text) {
    text = text || ''

    return text.split(tagRE)
}


function isCloseTag(segment, tagName) {
    const closeTagRE = /(<\/([a-zA-Z]\w*)\b[^>]*>)/
    const closeTag = segment.match(closeTagRE);
    return closeTag && closeTag[2] == tagName;
}

let counter = 0;

/**
 * Reverse segments with tag preserved
 */
function reverseSegments(segments, openedTag) {
	if (segments.length == 0) return [];

    const current = segments[0];
    const openTagRE = /(<([a-zA-Z]\w*)\b[^>]*>)/
    const openTag = current.match(openTagRE);
	if (openTag) {
        const tagName = openTag[2];
        const closeTagIndex = segments.findIndex(_ => isCloseTag(_, tagName));
        const closeTag = segments[closeTagIndex];

        const inside = segments.slice(1, closeTagIndex);
        const outside = segments.slice(closeTagIndex + 1);

        const reversedInside = reverseSegments(inside);
        const reversedOutside = reverseSegments(outside);

        return reversedOutside.concat([current]).concat(reversedInside).concat([closeTag]);

	} else {
        const reversed = current.split(' ').reverse().join(' ');
        const after = segments.slice(1);

	    return reverseSegments(after).concat([reversed]);
    }
}


/**
 * Reverse text with tag preserved
 */
function reverse(text) {
    text = text || '';
    const segments = tagSlice(text);
	return reverseSegments(segments).join('');
}


// ----------------------------------------------------------------
// Test
// ----------------------------------------------------------------
const origin = "Hello <b attr='some'>Bold <i>Italic</i> some words</b> World";
console.log(origin);
const reverseText = reverse(origin);
console.log(reverseText);

