// https://twitter.com/search?f=tweets&vertical=default&q=from%3Arealdonaldtrump%20since%3A2015-01-01%20until%3A2015-12-31include%3Aretweets&src=typd

// 2016-05_01

setInterval(function(){ scrollTo(0, document.body.scrollHeight) }, 2500)




var allTweets = []; var tweetElements = document.querySelectorAll('li.stream-item');
for (var i = 0; i < tweetElements.length; i++)
{
	var el = tweetElements[i]; var text = el.querySelector('.tweet-text').textContent;
	allTweets.push(text);
}
	 copy(allTweets);