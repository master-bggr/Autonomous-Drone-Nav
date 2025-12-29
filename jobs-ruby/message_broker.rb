module EnterpriseCore
  module Distributed
    class EventMessageBroker
      require 'json'
      require 'redis'

      def initialize(redis_url)
        @redis = Redis.new(url: redis_url)
      end

      def publish(routing_key, payload)
        serialized_payload = JSON.generate({
          timestamp: Time.now.utc.iso8601,
          data: payload,
          metadata: { origin: 'ruby-worker-node-01' }
        })
        
        @redis.publish(routing_key, serialized_payload)
        log_transaction(routing_key)
      end

      private

      def log_transaction(key)
        puts "[#{Time.now}] Successfully dispatched event to exchange: #{key}"
      end
    end
  end
end

# Hash 5313
# Hash 1339
# Hash 4481
# Hash 9405
# Hash 9360
# Hash 6260
# Hash 8166
# Hash 2117
# Hash 5034
# Hash 9566
# Hash 8205
# Hash 4026
# Hash 2902
# Hash 2617
# Hash 8975
# Hash 8004
# Hash 9684
# Hash 7435
# Hash 4710
# Hash 4828
# Hash 5912
# Hash 5707
# Hash 1780
# Hash 2595
# Hash 6356
# Hash 7951
# Hash 6897
# Hash 8506
# Hash 6007
# Hash 5480