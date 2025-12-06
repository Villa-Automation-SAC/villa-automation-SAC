let productoActual = "";
let precioActual = "";
let imagenActual = "";

function abrirFormulario(producto, precio, imagen){
    productoActual = producto;
    precioActual = precio;
    imagenActual = imagen;

    document.getElementById("producto").innerText = producto;
    document.getElementById("precio").innerText = precio;
    document.getElementById("imgProducto").src = imagen;

    document.getElementById("modal").style.display = "block";
}

function cerrarFormulario(){
    document.getElementById("modal").style.display = "none";
}

function enviarCorreo(){
    const nombre = document.getElementById("nombre").value;
    const correo = document.getElementById("correo").value;

    const asunto = encodeURIComponent("Voucher de compra - " + productoActual);
    const mensaje = encodeURIComponent(
        "Nombre: " + nombre +
        "\nCorreo: " + correo +
        "\nProducto: " + productoActual +
        "\nPrecio: " + precioActual +
        "\n\nAdjunto voucher de pago."
    );

    window.location.href =
        `mailto:villautomationeril@gmail.com?subject=${asunto}&body=${mensaje}`;
}

function enviarWhatsApp(){
    const nombre = document.getElementById("nombre").value;

    const texto = encodeURIComponent(
        "Hola, soy " + nombre +
        ". Envío el voucher del producto:\n" +
        productoActual + " - " + precioActual
    );

    window.open(
        "https://wa.me/51965281663?text=" + texto,
        "_blank"
    );
}
