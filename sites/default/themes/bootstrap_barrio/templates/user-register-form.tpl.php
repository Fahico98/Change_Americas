
<div class="container">
   <div id="edit-account" class="form-wrapper form-group">
      <input class="username" data-toggle="tooltip" type="hidden" name="name">
      <div class="form-item form-item-mail form-type-textfield form-group">
         <label class="control-label" for="edit-mail">
            Correo Electrónico <span class="form-required" title="Este campo es obligatorio">*</span>
         </label>
         <input class="form-control form-text required" title="dirección de correo electrónico"
            aria-describedby="edit-mail-help" data-toggle="tooltip" type="email" id="edit-mail" name="mail" size="60"
            maxlength="60" placeholder="correo electrónico" require>
         <small id="edit-mail-help" class="form-text text-muted">El correo debe de cumplir con la estructura estándar
             de direcciones de correo electrónicas iniciando con el usuario o identificador de usuario seguido del signo
             arroba <strong>(@)</strong>, nombre del servidor y dominio <strong>(.com, .co, .net, .org)</strong>.</small>
      </div>
      <div class="form-item form-type-textfield form-group">
         <label class="control-label" for="edit-pass">
            Contraseña <span class="form-required" title="Este campo es obligatorio">*</span>
         </label>
         <input class="form-control form-text required" title="contraseña" minlength="8" maxlength="14" aria-describedby="edit-pass-help"
            data-toggle="tooltip" type="password" id="edit-pass" name="pass" size="60" placeholder="contraseña" require>
         <small id="edit-pass-help" class="form-text text-muted">
            Su contraseña debe contar con un mínimo de <strong>8</strong> caracteres y un máximo de <strong>14</strong>, solo se
             aceptan caracteres alfanuméricos y no se aceptan caracteres especiales <strong>(% & ¿ ? * # +)</strong>. Al menos un
             caractér debe ser una letra mayúscula, una minúscula y no se pueden repetir mas de 3 caracteres contínuos.
         </small>
      </div>
      <div class="form-item form-type-textfield form-group">
         <label class="control-label" for="edit-empresa">
            Nombre de la Empresa <span class="form-required" title="Este campo es obligatorio">*</span>
         </label>
         <input class="form-control form-text required" title="nombre de la empresa" aria-describedby="edit-empresa-help"
            data-toggle="tooltip" type="text" id="edit-empresa" name="empresa" size="60" maxlength="60"
            placeholder="nombre de la empresa" require>
         <small id="edit-empresa-help" class="form-text text-muted">Ingrese el nombre de su empresa. <strong>Este campo es insensible a
             mayúsculas y minúsculas</strong>.</small>
      </div>
      <div class="form-item form-type-textfield form-group">
         <label class="control-label" for="edit-contacto">
            Persona de Contacto <span class="form-required" title="Este campo es obligatorio">*</span>
         </label>
         <input class="form-control form-text required" title="nombre de la persona de contacto"
            aria-describedby="edit-contacto-help" data-toggle="tooltip" type="text" id="edit-contacto" name="contacto"
            size="60" maxlength="60" placeholder="nombre de la persona de contacto" require>
         <small id="edit-contacto-help" class="form-text text-muted">Ingrese el nombre de la persona de contacto con quien nos
             comunicaremos.</small>
      </div>
      <div class="form-item form-type-textfield form-group">
         <label class="control-label" for="edit-cargo">
            Cargo <span class="form-required" title="Este campo es obligatorio">*</span>
         </label>
         <input class="form-control form-text required" title="cargo"
            aria-describedby="edit-cargo-help" data-toggle="tooltip" type="text" id="edit-cargo" name="cargo"
            size="60" maxlength="60" placeholder="cargo" require>
         <small id="edit-cargo-help" class="form-text text-muted">Por favor ingrese su cargo dentro de la empresa.</small>
      </div>
      <div class="form-item form-type-textfield form-group">
         <label class="control-label" for="edit-telefono">
            Telefono (opcional)
         </label>
         <input class="form-control form-text" title="número de telefono" aria-describedby="edit-telefono-help"
            data-toggle="tooltip" type="number" id="edit-telefono" name="telefono" size="60" maxlength="60"
            placeholder="número de telefono">
         <small id="edit-telefono-help" class="form-text text-muted">Por favor ingrese el número de telefono de la empresa.</small>
      </div>
      <input type="hidden" name="timezone" value="America/Bogota">
   </div>
   <input type="hidden" name="form_build_id" value="form-ay6eM1YqqhDWDeY3Aj1QEGHrtzNXhYGjjNpTFLQrbFI">
   <input type="hidden" name="form_id" value="user_register_form" />
   <div class="form-actions form-wrapper form-group" id="edit-actions">
      <button type="submit" id="edit-submit" name="op" value="Create new account" class="btn btn-success form-submit">
         Enviar Registro
      </button>
   </div>
</div>
