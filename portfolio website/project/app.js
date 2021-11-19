let emailElement = document.querySelector('#email');
let messageElement = document.querySelector('#message')
let submitButton = document.querySelector('#submit-button');
submitButton.addEventListener('click', function(e) {
    e.preventDefault();
    let emailValue = emailElement.value;
    let messageValue = messageElement.value;
    console.log('email:', emailValue);
    console.log('message:', messageValue);

    if(emailValue.includes('@')){
        alert('Thank you for your message!')
    }else{
        alert('Please enter a valid email adrress.')
    }
})
