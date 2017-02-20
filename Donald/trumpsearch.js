//https://twitter.com/search?l=&q=from%3ArealDonaldTrump%20since%3A2016-01-01%20until%3A2016-03-15&src=typd
// 2016-05_01

setInterval(function(){ scrollTo(0, document.body.scrollHeight) }, 2500)




var allTweets = []; var tweetElements = document.querySelectorAll('li.stream-item');
for (var i = 0; i < tweetElements.length; i++)
{
	var el = tweetElements[i]; var text = el.querySelector('.tweet-text').textContent;
	allTweets.push(text);
}
	 copy(allTweets);