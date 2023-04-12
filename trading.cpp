#include "trading.hpp"


double Pricer::norm_cdf(double x) {
    return (1.0 + std::erf(x / std::sqrt(2.0))) / 2.0;
}

double Pricer::black_scholes(const Stock& stock) {
    double stock_price = stock.underlying_price;
    double strike_price = stock.strike_price;
    double time_to_expiry = stock.expiration_time;
    double risk_free_rate = stock.interest_rate;
    double implied_volatility = stock.volatility;

    double d1 = (std::log(stock_price / strike_price) + (risk_free_rate +
     (implied_volatility * implied_volatility) / 2) * time_to_expiry) /
     (implied_volatility * std::sqrt(time_to_expiry));

    double d2 = d1 - implied_volatility * std::sqrt(time_to_expiry);

    double call_price = stock_price * norm_cdf(d1) - strike_price * 
    std::exp(-risk_free_rate * time_to_expiry) * norm_cdf(d2);

    double put_price = strike_price * std::exp(-risk_free_rate * time_to_expiry) * norm_cdf(-d2) - stock_price * norm_cdf(-d1);


    return call_price;
}

    