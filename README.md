# sample_project
Game engine useful code.  
C++ 20 needed. MSVC & Windows only.  
MSVC project files supplied.  

<div id="paypal-button-container-P-9BF190750N1558633MC7EZCA"></div>
<script src="https://www.paypal.com/sdk/js?client-id=AfuaDu1u5JTBdRo7DHkmdmvamFIMydBNyO29s1OyElagKU8RZwu8emMPvM57feLEYIUE7mDLCfIun1JE&vault=true&intent=subscription" data-sdk-integration-source="button-factory"></script> 
<script>
  paypal.Buttons({
      style: {
          shape: 'pill',
          color: 'gold',
          layout: 'vertical',
          label: 'subscribe'
      },
      createSubscription: function(data, actions) {
        return actions.subscription.create({
          /* Creates the subscription */
          plan_id: 'P-9BF190750N1558633MC7EZCA'
        });
      },
      onApprove: function(data, actions) {
        alert(data.subscriptionID); // You can add optional success message for the subscriber here
      }
  }).render('#paypal-button-container-P-9BF190750N1558633MC7EZCA'); // Renders the PayPal button
</script>

[![](https://www.paypalobjects.com/en_GB/i/btn/btn_subscribeCC_LG.gif)](https://www.paypal.com/cgi-bin/webscr?cmd=_s-xclick&hosted_button_id=D539LS3MUHBH4)
