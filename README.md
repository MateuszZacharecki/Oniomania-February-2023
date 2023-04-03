# Oniomania-February-2023 (IN PROGRESS...)
## Intro
As the battle dust after Christmas shopping haven't settled yet, let's simulate it.

## Description
Presents are bought in shops, of course (where they are goods). Every shop offers certain goods. A shop knows, how many items of every good it has got (it may be zero). Goods are identified by their names. Prices are set by a shop (the same good may have different prices in different shops).

The are various types of shops. Ordinary shops are... ordinary. Chains of shops are made up of certain number (in extreme cases of zero, but usually of large, much larger number) of ordinary shops. Chains can expand through taking over another ordinary shops or other chains (in second case all shops of taken over chain become shops of taking over chain). Chains can also shrink, when some ordinary shop leaves a chain or the whole chain is taken over. Being in chain means that every transaction goes through the chain. Prices in different shops in a chain may be different. A shop can't be in two (or more) chains in a moment. A chain asked for a good checks if there is a shop in the chain with the good and gives a price and number of items of the good in the shop. If plenty of shops have the same good, any shop is chosen. A chain adds a margin to shoppings.

The city keeps a list of all shops (chains and shops not connected in chains) and of citizens (customers).

Customers have some budget, which may be used for presents. Different customers use different strategies in shopping. Some of them have their favourite shop and always buy there using one of the strategies:
- Maximilizers buy the most expensive available present they can afford in their favourite shop
- Minimilizers buy the cheapest available present they can afford in their favourite shop
- Randomers try a few times (for instance 3 times, established number) to choose randomly chosen present (offered in the shop), if it's available (number of items is greater than zero) and randomer can afford it, he chooses it (and doesn't draw again), otherwise randomer draws again (if only he has any attempts to drawing left)

Others try to buy in any shops in city, however they look for particular product. It's assumed that they look for only one product during the simulation. Frugals collect a list of shops in the city, they find out about prices of product they're looking for in every shop and buy it in a shop where the product is the cheapest (if a few shops offer the same price for the product, they buy it in any of these shops). Traditionalists don't buy online and they look for the nearest shop that offers the product they look for (if there are a few shops in the same distance, they choose any of these shops). Every customer and every ordinary shop knows their position, represented by two real numbers x and y. Distance means the ordinary, Euclidean distance on a plane.

It may happen that some customer doesn't choose anything successfully.
