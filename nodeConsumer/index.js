const amqp = require('amqplib').connect('amqp://guest:guest@localhost'); 
const q    = "myqueue"; 

amqp.then(function(conn) {
    return conn.createChannel();
  }).then(function(ch) {
    const options = {
        durable: false
    }

    return ch.assertQueue(q, options).then(function(ok) {
      return ch.consume(q, function(msg) {
        if (msg !== null) {
          console.log(msg.content.toString());
          ch.ack(msg);
        }
      });
    });
  }).catch(console.warn);